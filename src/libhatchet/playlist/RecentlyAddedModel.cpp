/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2012, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include "RecentlyAddedModel.h"

#include <QMimeData>
#include <QTreeView>

#include "Source.h"
#include "SourceList.h"
#include "database/Database.h"
#include "database/DatabaseCommand_AllTracks.h"
#include "utils/HatchetUtils.h"
#include "utils/Logger.h"

#define LATEST_TRACK_ITEMS 250

using namespace Hatchet;


RecentlyAddedModel::RecentlyAddedModel( QObject* parent )
    : PlayableModel( parent )
    , m_limit( LATEST_TRACK_ITEMS )
{
}


RecentlyAddedModel::~RecentlyAddedModel()
{
}


void
RecentlyAddedModel::loadHistory()
{
    if ( rowCount( QModelIndex() ) )
    {
        clear();
    }
    startLoading();

    DatabaseCommand_AllTracks* cmd = new DatabaseCommand_AllTracks( m_source->dbCollection() );
    cmd->setLimit( m_limit );
    cmd->setSortOrder( DatabaseCommand_AllTracks::ModificationTime );
    cmd->setSortDescending( true );

    connect( cmd, SIGNAL( tracks( QList<Hatchet::query_ptr>, QVariant ) ),
                    SLOT( appendQueries( QList<Hatchet::query_ptr> ) ), Qt::QueuedConnection );

    Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );
}


void
RecentlyAddedModel::onSourcesReady()
{
    Q_ASSERT( m_source.isNull() );

    loadHistory();

    foreach ( const source_ptr& source, SourceList::instance()->sources() )
        onSourceAdded( source );
}


void
RecentlyAddedModel::setSource( const Hatchet::source_ptr& source )
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
        onSourceAdded( source );
        loadHistory();
    }
}


void
RecentlyAddedModel::onSourceAdded( const Hatchet::source_ptr& source )
{
    connect( source->dbCollection().data(), SIGNAL( changed() ), SLOT( loadHistory() ) );
}


bool
RecentlyAddedModel::isTemporary() const
{
    return true;
}
