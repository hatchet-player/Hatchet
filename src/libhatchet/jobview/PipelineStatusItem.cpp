/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *                        Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include "PipelineStatusItem.h"

#include "utils/HatchetUtilsGui.h"

#include "JobStatusModel.h"
#include "JobStatusView.h"
#include "Pipeline.h"
#include "Source.h"
#include "Track.h"


PipelineStatusItem::PipelineStatusItem( const Hatchet::query_ptr& q )
    : JobStatusItem()
{
    connect( Hatchet::Pipeline::instance(), SIGNAL( resolving( Hatchet::query_ptr ) ), this, SLOT( resolving( Hatchet::query_ptr ) ) );
    connect( Hatchet::Pipeline::instance(), SIGNAL( idle() ), this, SLOT( idle() ) );

    if ( !q.isNull() )
        resolving( q );
}


PipelineStatusItem::~PipelineStatusItem()
{
}


QString
PipelineStatusItem::rightColumnText() const
{
    return QString( "%1" ).arg( Hatchet::Pipeline::instance()->activeQueryCount() + Hatchet::Pipeline::instance()->pendingQueryCount() );
}


QString
PipelineStatusItem::mainText() const
{
    return m_latestQuery;
}


void
PipelineStatusItem::idle()
{
    if ( !Hatchet::Pipeline::instance()->activeQueryCount() )
        emit finished();
}


QPixmap
PipelineStatusItem::icon() const
{
    return HatchetUtils::defaultPixmap( HatchetUtils::Search );
}


void
PipelineStatusItem::resolving( const Hatchet::query_ptr& query )
{
    if ( query->isFullTextQuery() )
        m_latestQuery = query->fullTextQuery();
    else
        m_latestQuery = QString( "%1 - %2" ).arg( query->queryTrack()->artist() ).arg( query->queryTrack()->track() );

    Q_ASSERT( !m_latestQuery.isEmpty() );

    emit statusChanged();
}


PipelineStatusManager::PipelineStatusManager( QObject* parent )
    : QObject( parent )
{
    connect( Hatchet::Pipeline::instance(), SIGNAL( resolving( Hatchet::query_ptr ) ), this, SLOT( resolving( Hatchet::query_ptr ) ) );
}


void
PipelineStatusManager::resolving( const Hatchet::query_ptr& p )
{
    Q_UNUSED( p );

    if ( m_curItem.isNull() )
    {
        // No current query item and we're resolving something, so show it
        m_curItem = QPointer< PipelineStatusItem >( new PipelineStatusItem( p ) );
        JobStatusView::instance()->model()->addJob( m_curItem.data() );
    }
}
