/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
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

#include "collection/Collection.h"

#include "accounts/AccountManager.h"
#include "playlist/PlaylistUpdaterInterface.h"
#include "utils/Closure.h"
#include "utils/ImageRegistry.h"
#include "utils/Logger.h"

#include "PlaylistEntry.h"
#include "Source.h"

#include <QMetaObject>
#include <QGenericArgument>

using namespace Hatchet;


Collection::Collection( const source_ptr& source, const QString& name, QObject* parent )
    : Resolver( parent )
    , m_name( name )
    , m_lastmodified( 0 )
    , m_changed( false )
    , m_source( source )
{
    qDebug() << Q_FUNC_INFO << name << source->friendlyName();

    connect( source.data(), SIGNAL( synced() ), SLOT( onSynced() ) );
}


Collection::~Collection()
{
    qDebug() << Q_FUNC_INFO;
}


void
Collection::setWeakRef( const collection_wptr& weakRef )
{
    m_ownRef = weakRef;
}


collection_wptr
Collection::weakRef() const
{
    return m_ownRef;
}


QSet< Collection::BrowseCapability >
Collection::browseCapabilities() const
{
    return m_browseCapabilities;
}


QString
Collection::name() const
{
    return m_name;
}


QString
Collection::prettyName() const
{
    return tr( "Collection" );
}


QString
Collection::description() const
{
    return QString();
}


QString
Collection::itemName() const
{
    return tr( "Collection" );
}


QPixmap
Collection::icon( const QSize& size ) const
{
    return ImageRegistry::instance()->pixmap( RESPATH "images/collection.svg", size );
}


QPixmap
Collection::bigIcon() const
{
    if ( !source()->avatar().isNull() )
        return source()->avatar( HatchetUtils::RoundedCorners );

    return HatchetUtils::tinted( HatchetUtils::defaultPixmap( HatchetUtils::DefaultCollection ), Qt::white );
}


bool
Collection::isLocal() const
{
    return false;
}


source_ptr
Collection::source() const
{
    return m_source;
}


int
Collection::trackCount() const
{
    return -1;
}


void
Collection::addPlaylist( const Hatchet::playlist_ptr& p )
{
    if ( m_playlists.contains( p->guid() ) )
        return;

    QList<playlist_ptr> toadd;
    toadd << p;
    m_playlists.insert( p->guid(), p );

/*    qDebug() << Q_FUNC_INFO << "Collection name" << name()
                            << "from source id" << source()->id()
                            << "numplaylists:" << m_playlists.count();*/
    emit playlistsAdded( toadd );
}


void
Collection::addAutoPlaylist( const Hatchet::dynplaylist_ptr& p )
{
    QList<dynplaylist_ptr> toadd;
    toadd << p;
    m_autoplaylists.insert( p->guid(), p );

/*    qDebug() << Q_FUNC_INFO << "Collection name" << name()
                            << "from source id" << source()->id()
                            << "numplaylists:" << m_playlists.count();*/
    emit autoPlaylistsAdded( toadd );
}


void
Collection::addStation( const dynplaylist_ptr& s )
{
    QList<dynplaylist_ptr> toadd;
    toadd << s;
    m_stations.insert( s->guid(), s );

/*    qDebug() << Q_FUNC_INFO << "Collection name" << name()
                            << "from source id" << source()->id()
                            << "numplaylists:" << m_playlists.count();*/
    emit stationsAdded( toadd );
}


void
Collection::deletePlaylist( const Hatchet::playlist_ptr& p )
{
    QList<playlist_ptr> todelete;
    todelete << p;
    m_playlists.remove( p->guid() );

/*    qDebug() << Q_FUNC_INFO << "Collection name" << name()
                            << "from source id" << source()->id()
                            << "numplaylists:" << m_playlists.count();*/
    emit playlistsDeleted( todelete );
}


void
Collection::deleteAutoPlaylist( const Hatchet::dynplaylist_ptr& p )
{
    QList<dynplaylist_ptr> todelete;
    todelete << p;
    m_autoplaylists.remove( p->guid() );

/*    qDebug() << Q_FUNC_INFO << "Collection name" << name()
                            << "from source id" << source()->id()
                            << "numplaylists:" << m_playlists.count();*/
    emit autoPlaylistsDeleted( todelete );
}


void
Collection::deleteStation( const dynplaylist_ptr& s )
{
    QList<dynplaylist_ptr> todelete;
    todelete << s;
    m_stations.remove( s->guid() );

/*    qDebug() << Q_FUNC_INFO << "Collection name" << name()
                            << "from source id" << source()->id()
                            << "numplaylists:" << m_playlists.count();*/
    emit stationsDeleted( todelete );
}


Hatchet::playlist_ptr
Collection::playlist( const QString& guid )
{
    return m_playlists.value( guid, Hatchet::playlist_ptr() );
}


Hatchet::dynplaylist_ptr
Collection::autoPlaylist( const QString& guid )
{
    return m_autoplaylists.value( guid, Hatchet::dynplaylist_ptr() );
}


Hatchet::dynplaylist_ptr
Collection::station( const QString& guid )
{
    return m_stations.value( guid, Hatchet::dynplaylist_ptr() );
}


void
Collection::setPlaylists( const QList<Hatchet::playlist_ptr>& plists )
{
    foreach ( const playlist_ptr& p, plists )
    {
//        qDebug() << "Batch inserting playlist:" << p->guid();
        m_playlists.insert( p->guid(), p );
        if ( !m_source.isNull() && m_source->isLocal() )
        {
            if ( Hatchet::Accounts::AccountManager::instance()->isReady() )
                doLoadPlaylistUpdater( p );
            else
                NewClosure( Hatchet::Accounts::AccountManager::instance(), SIGNAL( ready() ),
                            this, SLOT( doLoadPlaylistUpdater( playlist_ptr ) ), p );
        }
    }
    emit playlistsAdded( plists );
}


void
Collection::doLoadPlaylistUpdater( const playlist_ptr& p )
{
    PlaylistUpdaterInterface::loadForPlaylist( p );
}


void
Collection::setAutoPlaylists( const QList< Hatchet::dynplaylist_ptr >& plists )
{
    foreach ( const dynplaylist_ptr& p, plists )
    {
//        qDebug() << "Batch inserting dynamic playlist:" << p->guid();
        m_autoplaylists.insert( p->guid(), p );
    }
    emit autoPlaylistsAdded( plists );
}


void
Collection::setStations( const QList< dynplaylist_ptr >& stations )
{
    foreach ( const dynplaylist_ptr& s, stations )
    {
//        qDebug() << "Batch inserting station:" << s->guid();
        m_stations.insert( s->guid(), s );
    }
    emit autoPlaylistsAdded( stations );
}


void
Collection::setTracks( const QList<unsigned int>& ids )
{
    tDebug() << Q_FUNC_INFO << ids.count() << name();

    m_changed = true;
    emit tracksAdded( ids );
}


void
Collection::delTracks( const QList<unsigned int>& ids )
{
    tDebug() << Q_FUNC_INFO << ids.count() << name();

    m_changed = true;
    emit tracksRemoved( ids );
}


void
Collection::onSynced()
{
    tDebug( LOGVERBOSE ) << Q_FUNC_INFO << m_changed;

    if ( m_changed )
    {
        m_changed = false;
        emit changed();
    }
}


void
Collection::moveAutoToStation( const QString& guid )
{
    if ( m_autoplaylists.contains( guid ) )
        m_stations.insert( guid, m_autoplaylists.take( guid ) );
}


void
Collection::moveStationToAuto( const QString& guid )
{
    if ( m_stations.contains( guid ) )
        m_autoplaylists.insert( guid, m_stations.take( guid ) );
}


void
Collection::loadPlaylists()
{
    qDebug() << Q_FUNC_INFO;
}


void
Collection::loadAutoPlaylists()
{
    qDebug() << Q_FUNC_INFO;
}


void
Collection::loadStations()
{
    qDebug() << Q_FUNC_INFO;
}