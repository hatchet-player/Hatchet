/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2011, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2013, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include "RecentlyPlayedPlaylistsModel.h"

#include "audio/AudioEngine.h"
#include "collection/Collection.h"
#include "playlist/dynamic/DynamicPlaylist.h"
#include "utils/Logger.h"

#include "Playlist.h"
#include "PlaylistEntry.h"
#include "PlaylistInterface.h"
#include "SourceList.h"
#include "HatchetSettings.h"
#include "Track.h"

using namespace Hatchet;


RecentlyPlayedPlaylistsModel::RecentlyPlayedPlaylistsModel( QObject* parent )
    : QAbstractListModel( parent )
    , m_maxPlaylists( 0 )
    , m_waitingForSome( true )
{
    loadFromSettings();

    connect( SourceList::instance(), SIGNAL( sourceAdded( Hatchet::source_ptr ) ), this, SLOT( onSourceAdded( Hatchet::source_ptr ) ), Qt::QueuedConnection );
    connect( HatchetSettings::instance(), SIGNAL( recentlyPlayedPlaylistAdded( QString, int ) ), this, SLOT( plAdded( QString, int ) ) );
    connect( AudioEngine::instance(),SIGNAL( playlistChanged( Hatchet::playlistinterface_ptr ) ), this, SLOT( playlistChanged( Hatchet::playlistinterface_ptr ) ), Qt::QueuedConnection );

    emit emptinessChanged( m_recplaylists.isEmpty() );
}


void
RecentlyPlayedPlaylistsModel::loadFromSettings()
{
//    qDebug() << Q_FUNC_INFO;
    if ( !m_waitingForSome )
        return;

    beginResetModel();
    m_recplaylists.clear();
    m_waitingForSome = false;

    QStringList playlist_guids = HatchetSettings::instance()->recentlyPlayedPlaylistGuids( m_maxPlaylists );

    for( int i = playlist_guids.size() - 1; i >= 0; i-- )
    {
//        qDebug() << "loading playlist" << playlist_guids[i];

        playlist_ptr pl = m_cached.value( playlist_guids[i], Hatchet::playlist_ptr() );
        if ( !pl )
            pl = Hatchet::Playlist::get( playlist_guids[i] );
        if ( !pl )
            pl = Hatchet::DynamicPlaylist::get( playlist_guids[i] );

        if ( pl )
        {
            m_recplaylists << pl;

            if ( !m_cached.contains( playlist_guids[i] ) )
            {
                if ( pl.dynamicCast< DynamicPlaylist >().isNull() )
                    connect( pl.data(), SIGNAL(revisionLoaded(Hatchet::PlaylistRevision)), this, SLOT(playlistRevisionLoaded()) );
                else
                    connect( pl.data(), SIGNAL(dynamicRevisionLoaded(Hatchet::DynamicPlaylistRevision)), this, SLOT(playlistRevisionLoaded()) );
                m_cached[playlist_guids[i]] = pl;
            }
        } else
            m_waitingForSome = true;
    }
    endResetModel();

    emit emptinessChanged( m_recplaylists.isEmpty() );
}


QVariant
RecentlyPlayedPlaylistsModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() || !hasIndex( index.row(), index.column(), index.parent() ) )
        return QVariant();

    playlist_ptr pl = m_recplaylists[index.row()];
    switch( role )
    {
    case Qt::DisplayRole:
        return pl->title();
    case PlaylistRole:
        return QVariant::fromValue< Hatchet::playlist_ptr >( pl );
    case ArtistRole:
    {
        if ( m_artists.value( pl ).isEmpty() )
        {
            QStringList artists;

            foreach ( const Hatchet::plentry_ptr& entry, pl->entries() )
            {
                if ( !artists.contains( entry->query()->track()->artist() ) )
                    artists << entry->query()->track()->artist();
            }

            m_artists[pl] = artists.join( ", " );
        }

        return m_artists[pl];
    }
    case PlaylistTypeRole:
    {
        if ( !pl.dynamicCast< Hatchet::DynamicPlaylist >().isNull() )
        {
            dynplaylist_ptr dynp = pl.dynamicCast< Hatchet::DynamicPlaylist >();
            if ( dynp->mode() == Static )
                return AutoPlaylist;
            else if ( dynp->mode() == OnDemand )
                return Station;
        } else
        {
            return StaticPlaylist;
        }
    }
    case DynamicPlaylistRole:
    {
        dynplaylist_ptr dynp = pl.dynamicCast< Hatchet::DynamicPlaylist >();
        return QVariant::fromValue< Hatchet::dynplaylist_ptr >( dynp );
    }
    case TrackCountRole:
    {
        if ( !pl.dynamicCast< Hatchet::DynamicPlaylist >().isNull() && pl.dynamicCast< Hatchet::DynamicPlaylist >()->mode() == OnDemand )
            return QString( QChar( 0x221E ) );
        else
            return pl->entries().count();
    }
    default:
        return QVariant();
    }
}


void
RecentlyPlayedPlaylistsModel::playlistRevisionLoaded()
{
    Playlist* p = qobject_cast< Playlist* >( sender() );
    Q_ASSERT( p );

    for ( int i = 0; i < m_recplaylists.size(); i++ )
    {
        if ( m_recplaylists[ i ]->guid() == p->guid() )
        {
            QModelIndex idx = index( i, 0, QModelIndex() );
            emit dataChanged( idx, idx );
        }
    }
}


void
RecentlyPlayedPlaylistsModel::onSourceAdded( const Hatchet::source_ptr& source )
{
    connect( source.data(), SIGNAL( online() ),
                              SLOT( sourceOnline() ) );

    connect( source->dbCollection().data(), SIGNAL( playlistsAdded( QList<Hatchet::playlist_ptr> ) ),
                                              SLOT( loadFromSettings() ) );
    connect( source->dbCollection().data(), SIGNAL( playlistsDeleted( QList<Hatchet::playlist_ptr> ) ),
                                              SLOT( onPlaylistsRemoved( QList<Hatchet::playlist_ptr> ) ) );
}


void
RecentlyPlayedPlaylistsModel::sourceOnline()
{
    Source* s = qobject_cast< Source* >( sender() );
    Q_ASSERT( s );

    for ( int i = 0; i < m_recplaylists.size(); i++ )
    {
        if ( m_recplaylists[ i ]->author().data() == s )
        {
            QModelIndex idx = index( i, 0, QModelIndex() );
            emit dataChanged( idx, idx );
        }
    }
}


void
RecentlyPlayedPlaylistsModel::onPlaylistsRemoved( QList< playlist_ptr > playlists )
{
    foreach ( const playlist_ptr& pl, playlists )
    {
        if ( m_recplaylists.contains( pl ) )
        {
            m_artists.remove( pl );
            m_cached.remove( pl->guid() );

            int idx = m_recplaylists.indexOf( pl );
            beginRemoveRows( QModelIndex(), idx, idx );
            m_recplaylists.removeAt( idx );
            endRemoveRows();
        }
    }

    emit emptinessChanged( m_recplaylists.isEmpty() );
}


int
RecentlyPlayedPlaylistsModel::rowCount( const QModelIndex& ) const
{
    return m_recplaylists.count();
}


void
RecentlyPlayedPlaylistsModel::plAdded( const QString& plguid, int sourceId )
{
    Q_UNUSED( sourceId );
    const playlist_ptr& pl = Playlist::get( plguid );
    if ( !pl )
        return;

    onPlaylistsRemoved( QList< playlist_ptr >() << pl );

    beginInsertRows( QModelIndex(), 0, 0 );
    m_recplaylists.prepend( pl );;
    endInsertRows();

    emit emptinessChanged( m_recplaylists.isEmpty() );
}


void
RecentlyPlayedPlaylistsModel::playlistChanged( Hatchet::playlistinterface_ptr pli )
{
    // ARG
    if ( !pli )
        return;

    if ( Playlist *pl = dynamic_cast< Playlist* >( pli.data() ) )
    {
        // look for it, qsharedpointer fail
        playlist_ptr ptr;
        foreach ( const playlist_ptr& test, m_recplaylists )
        {
            if ( test.data() == pl )
                ptr = test;
        }

        if ( ptr && m_artists.contains( ptr ) )
        {
            m_artists[ ptr ] = QString();
        }

        QModelIndex idx = index( m_recplaylists.indexOf( ptr ), 0, QModelIndex() );
        emit dataChanged( idx, idx );
    }
}
