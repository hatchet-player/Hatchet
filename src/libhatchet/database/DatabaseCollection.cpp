/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi            <lfranchi@kde.org>
 *   Copyright 2013,      Teo Mrnjavac <teo@kde.org>
 *
 *   Hatchet is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hatchet is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hatchet. If not, see <http://www.gnu.org/licenses/>.
 */

#include "DatabaseCollection.h"

#include "database/Database.h"
#include "database/DatabaseCommand_AllArtists.h"
#include "database/DatabaseCommand_AllAlbums.h"
#include "database/DatabaseCommand_AllTracks.h"
#include "database/DatabaseCommand_AddFiles.h"
#include "database/DatabaseCommand_DeleteFiles.h"
#include "database/DatabaseCommand_LoadAllPlaylists.h"
#include "database/DatabaseCommand_LoadAllAutoPlaylists.h"
#include "database/DatabaseCommand_LoadAllStations.h"
#include "utils/Logger.h"

#include "PlaylistEntry.h"

using namespace Hatchet;


DatabaseCollection::DatabaseCollection( const source_ptr& src, QObject* parent )
    : Collection( src, QString( "dbcollection:%1" ).arg( src->nodeId() ), parent )
{
    m_browseCapabilities
        << CapabilityBrowseArtists
        << CapabilityBrowseAlbums
        << CapabilityBrowseTracks;


    connect( source().data(), SIGNAL( online() ), SIGNAL( online() ) );
    connect( source().data(), SIGNAL( offline() ), SIGNAL( offline() ) );
}


bool
DatabaseCollection::isOnline() const
{
    return source()->isOnline();
}


void
DatabaseCollection::loadPlaylists()
{
    DatabaseCommand_LoadAllPlaylists* cmd = new DatabaseCommand_LoadAllPlaylists( source() );

    connect( cmd,  SIGNAL( done( const QList<Hatchet::playlist_ptr>& ) ),
                     SLOT( setPlaylists( const QList<Hatchet::playlist_ptr>& ) ) );

    Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );
}


void
DatabaseCollection::loadAutoPlaylists()
{
    DatabaseCommand_LoadAllAutoPlaylists* cmd = new DatabaseCommand_LoadAllAutoPlaylists( source() );

    connect( cmd, SIGNAL( autoPlaylistLoaded( Hatchet::source_ptr, QVariantList ) ),
                    SLOT( autoPlaylistCreated( const Hatchet::source_ptr&, const QVariantList& ) ) );

    Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );
}


void
DatabaseCollection::loadStations()
{
    DatabaseCommand_LoadAllStations* cmd = new DatabaseCommand_LoadAllStations( source() );

    connect( cmd, SIGNAL( stationLoaded( Hatchet::source_ptr, QVariantList ) ),
             SLOT( stationCreated( const Hatchet::source_ptr&, const QVariantList& ) ) );

    Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );
}


void
DatabaseCollection::addTracks( const QList<QVariant>& newitems )
{
    qDebug() << Q_FUNC_INFO << newitems.length();
    DatabaseCommand_AddFiles* cmd = new DatabaseCommand_AddFiles( newitems, source() );

    Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );
}


void
DatabaseCollection::removeTracks( const QDir& dir )
{
    qDebug() << Q_FUNC_INFO << dir;
    DatabaseCommand_DeleteFiles* cmd = new DatabaseCommand_DeleteFiles( dir, source() );

    Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );
}


QList< Hatchet::playlist_ptr >
DatabaseCollection::playlists()
{
    if ( Collection::playlists().isEmpty() )
    {
        loadPlaylists();
    }

    return Collection::playlists();
}


QList< dynplaylist_ptr >
DatabaseCollection::autoPlaylists()
{
    // echonest is dead, disable all echonest code
    /*
    if ( Collection::autoPlaylists().isEmpty() )
    {
        loadAutoPlaylists();
    }
    */

    return Collection::autoPlaylists();
}


QList< dynplaylist_ptr >
DatabaseCollection::stations()
{
    // echonest is dead, disable all echonest code
    /*
    if ( Collection::stations().isEmpty() )
    {
        loadStations();
    }
    */

    return Collection::stations();
}


Hatchet::ArtistsRequest*
DatabaseCollection::requestArtists()
{
    //FIXME: assuming there's only one dbcollection per source, and that this is the one
    Hatchet::collection_ptr thisCollection = source()->dbCollection();
    if ( thisCollection->name() != this->name() )
        return 0;

    Hatchet::ArtistsRequest* cmd = new DatabaseCommand_AllArtists( thisCollection );

    return cmd;
}


Hatchet::AlbumsRequest*
DatabaseCollection::requestAlbums( const Hatchet::artist_ptr& artist )
{
    //FIXME: assuming there's only one dbcollection per source, and that this is the one
    Hatchet::collection_ptr thisCollection = source()->dbCollection();
    if ( thisCollection->name() != this->name() )
        return 0;

    Hatchet::AlbumsRequest* cmd = new DatabaseCommand_AllAlbums( thisCollection, artist );

    return cmd;
}


Hatchet::TracksRequest*
DatabaseCollection::requestTracks( const Hatchet::album_ptr& album )
{
    //FIXME: assuming there's only one dbcollection per source, and that this is the one
    Hatchet::collection_ptr thisCollection = source()->dbCollection();
    if ( thisCollection->name() != this->name() )
        return 0;

    DatabaseCommand_AllTracks* cmd = new DatabaseCommand_AllTracks( thisCollection );

    if ( album )
    {
        cmd->setAlbum( album->weakRef() );
        cmd->setSortOrder( DatabaseCommand_AllTracks::AlbumPosition );
    }

    return cmd;
}


int
DatabaseCollection::trackCount() const
{
    return source()->trackCount();
}


QPixmap
DatabaseCollection::icon( const QSize& size ) const
{
    return source()->avatar( HatchetUtils::RoundedCorners, size, true );
}


void
DatabaseCollection::autoPlaylistCreated( const source_ptr& source, const QVariantList& data )
{
    dynplaylist_ptr p( new DynamicPlaylist( source,                  //src
                                            data[0].toString(),  //current rev
                                            data[1].toString(),  //title
                                            data[2].toString(),  //info
                                            data[3].toString(),  //creator
                                            data[4].toUInt(),  // createdOn
                                            data[5].toString(),  // dynamic type
                                            static_cast<GeneratorMode>(data[6].toInt()),  // dynamic mode
                                            data[7].toBool(),    //shared
                                            data[8].toInt(),     //lastmod
                                            data[9].toString() ), &QObject::deleteLater );  //GUID
    p->setWeakSelf( p.toWeakRef() );

    addAutoPlaylist( p );
}


void
DatabaseCollection::stationCreated( const source_ptr& source, const QVariantList& data )
{
    dynplaylist_ptr p( new DynamicPlaylist( source,                  //src
                                            data[0].toString(),  //current rev
                                            data[1].toString(),  //title
                                            data[2].toString(),  //info
                                            data[3].toString(),  //creator
                                            data[4].toUInt(),  // createdOn
                                            data[5].toString(),  // dynamic type
                                            static_cast<GeneratorMode>(data[6].toInt()),  // dynamic mode
                                            data[7].toBool(),    //shared
                                            data[8].toInt(),     //lastmod
                                            data[9].toString() ), &QObject::deleteLater );  //GUID
    p->setWeakSelf( p.toWeakRef() );

    addStation( p );
}



/*
 * Resolver interface
 *
 * We implement searching the database in the DatabaseResolver which avoids a n+1 query here.
 * We can't simply let ScriptCollection inherit Collection and Resolver because both are QObjects,
 * although Resolver doesn't need to be a QObject atm, blocking adding signals/slots to Resolver
 * in future seems to me worse than violating Liskov's law here. ~ domme
 */
unsigned int
DatabaseCollection::timeout() const
{
    return 0;
}


unsigned int
DatabaseCollection::weight() const
{
    return 0;
}


void
DatabaseCollection::resolve( const Hatchet::query_ptr& query )
{
    Q_UNUSED( query );
    Q_ASSERT(false);
}
