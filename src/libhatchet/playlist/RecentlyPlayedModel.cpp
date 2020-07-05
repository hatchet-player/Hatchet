/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include "RecentlyPlayedModel.h"

#include <QMimeData>
#include <QTreeView>

#include "Source.h"
#include "SourceList.h"
#include "database/Database.h"
#include "database/DatabaseCommand_PlaybackHistory.h"
#include "PlayableItem.h"
#include "utils/HatchetUtils.h"
#include "utils/Logger.h"

#define HISTORY_TRACK_ITEMS 25

using namespace Hatchet;


RecentlyPlayedModel::RecentlyPlayedModel( QObject* parent, unsigned int maxItems )
    : PlayableModel( parent )
    , m_limit( maxItems > 0 ? maxItems : HISTORY_TRACK_ITEMS )
{
}


RecentlyPlayedModel::~RecentlyPlayedModel()
{
}


void
RecentlyPlayedModel::loadHistory()
{
    if ( rowCount( QModelIndex() ) )
    {
        clear();
    }
    startLoading();

    DatabaseCommand_PlaybackHistory* cmd = new DatabaseCommand_PlaybackHistory( m_source );
    cmd->setDateFrom( m_dateFrom );
    cmd->setDateTo( m_dateTo );
    cmd->setLimit( m_limit );

    connect( cmd, SIGNAL( tracks( QList<Hatchet::track_ptr>, QList<Hatchet::PlaybackLog> ) ),
                    SLOT( onTracksLoaded( QList<Hatchet::track_ptr>, QList<Hatchet::PlaybackLog> ) ), Qt::QueuedConnection );

    Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );
}


void
RecentlyPlayedModel::onSourcesReady()
{
    Q_ASSERT( m_source.isNull() );

    loadHistory();

    foreach ( const source_ptr& source, SourceList::instance()->sources() )
        onSourceAdded( source );
}


void
RecentlyPlayedModel::setSource( const Hatchet::source_ptr& source )
{
    m_source = source;
    if ( source.isNull() )
    {
        if ( SourceList::instance()->isReady() )
            onSourcesReady();
        else
            connect( SourceList::instance(), SIGNAL( ready() ), SLOT( onSourcesReady() ) );

        connect( SourceList::instance(), SIGNAL( sourceAdded( Hatchet::source_ptr ) ), SLOT( onSourceAdded( Hatchet::source_ptr ) ) );
    }
    else
    {
        loadHistory();
        onSourceAdded( source );
    }
}


void
RecentlyPlayedModel::onSourceAdded( const Hatchet::source_ptr& source )
{
    connect( source.data(), SIGNAL( playbackFinished( Hatchet::track_ptr, Hatchet::PlaybackLog ) ),
                              SLOT( onPlaybackFinished( Hatchet::track_ptr, Hatchet::PlaybackLog ) ), Qt::UniqueConnection );

    int c = rowCount( QModelIndex() );
    emit beginInsertRows( QModelIndex(), c, c );

    PlayableItem* item = new PlayableItem( source, rootItem() );
    item->index = createIndex( rootItem()->children.count() - 1, 0, item );
    connect( item, SIGNAL( dataChanged() ), SLOT( onDataChanged() ) );

    emit endInsertRows();
}


void
RecentlyPlayedModel::onPlaybackFinished( const Hatchet::track_ptr& track, const Hatchet::PlaybackLog& log )
{
    const QModelIndex parent = indexFromSource( log.source );
    const int count = rowCount( parent );
    if ( count )
    {
        PlayableItem* oldestItem = itemFromIndex( index( count - 1, 0, parent ) );
        if ( oldestItem->playbackLog().timestamp >= log.timestamp )
        {
            if ( count >= (int)m_limit )
                return;

            insertQuery( track->toQuery(), count, log, parent );
            return;
        }

        PlayableItem* youngestItem = itemFromIndex( index( 0, 0, parent ) );
        if ( youngestItem->playbackLog().timestamp <= log.timestamp )
        {
            insertQuery( track->toQuery(), 0, log, parent );
        }
        else
        {
            for ( int i = 0; i < count - 1; i++ )
            {
                PlayableItem* item1 = itemFromIndex( index( i, 0, parent ) );
                PlayableItem* item2 = itemFromIndex( index( i + 1, 0, parent ) );

                if ( item1->playbackLog().timestamp >= log.timestamp && item2->playbackLog().timestamp <= log.timestamp )
                {
                    insertQuery( track->toQuery(), i + 1, log, parent );
                    break;
                }
            }
        }
    }
    else
        insertQuery( track->toQuery(), 0, log, parent );

    if ( rowCount( parent ) > (int)m_limit )
        remove( m_limit, false, parent );

    emit dataChanged( parent, parent );
    ensureResolved();
}


void
RecentlyPlayedModel::onTracksLoaded( QList<Hatchet::track_ptr> tracks, QList<Hatchet::PlaybackLog> logs )
{
    finishLoading();
    for ( int i = 0; i < tracks.count(); i++ )
    {
        onPlaybackFinished( tracks.at( i ), logs.at( i ) );
    }
    ensureResolved();
}


bool
RecentlyPlayedModel::isTemporary() const
{
    return true;
}


void
RecentlyPlayedModel::setDateFrom( const QDate& date )
{
    m_dateFrom = date;
}


void
RecentlyPlayedModel::setDateTo( const QDate& date )
{
    m_dateTo = date;
    loadHistory();
}
