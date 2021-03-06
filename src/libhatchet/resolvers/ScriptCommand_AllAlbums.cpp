/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Teo Mrnjavac <teo@kde.org>
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

#include "ScriptCommand_AllAlbums.h"

#include "utils/Logger.h"

#include "Album.h"
#include "Artist.h"
#include "ScriptAccount.h"
#include "PlaylistEntry.h"
#include "ScriptCollection.h"
#include "ScriptJob.h"
#include "ScriptCommand_AllArtists.h"

using namespace Hatchet;

ScriptCommand_AllAlbums::ScriptCommand_AllAlbums( const Hatchet::collection_ptr& collection,
                                                  const Hatchet::artist_ptr& artist,
                                                  QObject* parent )
    : ScriptCommand( parent )
    , m_collection( collection )
    , m_artist( artist )
{
}


void
ScriptCommand_AllAlbums::enqueue()
{
    Hatchet::ScriptCollection* collection = qobject_cast< Hatchet::ScriptCollection* >( m_collection.data() );
    if ( collection == 0 )
    {
        emit albums( QList< Hatchet::album_ptr >() );
        return;
    }

    exec();
}


void
ScriptCommand_AllAlbums::setFilter( const QString& filter )
{
    m_filter = filter;
}


void
ScriptCommand_AllAlbums::exec()
{
    Hatchet::ScriptCollection* collection = qobject_cast< Hatchet::ScriptCollection* >( m_collection.data() );
    if ( collection == 0 )
    {
        reportFailure();
        return;
    }

    QString methodName;
    QVariantMap arguments;

    if ( m_artist )
    {
        methodName = "artistAlbums";
        arguments[ "artist" ] = m_artist->name();
    }
    else
    {
        methodName = "albums";
    }

    if ( !m_filter.isEmpty() )
    {
        arguments[ "filter" ] = m_filter;
    }

    ScriptJob* job = collection->scriptObject()->invoke( methodName, arguments );
    connect( job, SIGNAL( done( QVariantMap ) ), SLOT( onAlbumsJobDone( QVariantMap ) ), Qt::QueuedConnection );
    job->start();
}


void
ScriptCommand_AllAlbums::reportFailure()
{
    if ( m_artist )
        tDebug() << Q_FUNC_INFO << "for collection" << m_collection->name() << "and artist" << m_artist->name();

    emit albums( QList< Hatchet::album_ptr >() );
    emit done();
}


void
ScriptCommand_AllAlbums::onAlbumsJobDone( const QVariantMap& result )
{
    ScriptJob* job = qobject_cast< ScriptJob* >( sender() );
    Q_ASSERT( job );

    if ( job->error() )
    {
        reportFailure();
        return;
    }

    QList< Hatchet::artist_ptr > resultArtists;
    if ( !result["artists"].toList().isEmpty() )
    {
        resultArtists = ScriptCommand_AllArtists::parseArtistVariantList( result[ "artists" ].toList() );
    }
    else
    {
        resultArtists << m_artist;
    }

    QList< Hatchet::album_ptr > a = parseAlbumVariantList( resultArtists, result[ "albums" ].toList() );
    emit albums( a );
    emit done();

    job->deleteLater();
}


QList< Hatchet::album_ptr >
ScriptCommand_AllAlbums::parseAlbumVariantList( const QList< Hatchet::artist_ptr >& artists, const QVariantList& reslist )
{
    QList< Hatchet::album_ptr > results;

    if ( artists.length() != 1 && reslist.length() != artists.length() )
    {
        tLog() << "artists" << artists.length();
        tLog() << "albums" << reslist.length();
        Q_ASSERT(false);
        tLog() << "Got invalid collection albums response where artists and albums don't match";
        return results;
    }

    bool useArtistList = ( artists.length() > 1 );
    for( int i = 0; i < reslist.length(); i++ )
    {
        const QString val = reslist[ i ].toString();
        if ( val.trimmed().isEmpty() )
            continue;

        if ( useArtistList )
        {
            results << Hatchet::Album::get( artists[ i ], val, false );
        }
        else
        {
            results << Hatchet::Album::get( artists[ 0 ], val, false );
        }
    }

    return results;
}
