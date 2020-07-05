/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
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

#include "GroupItem.h"

#include "utils/HatchetUtils.h"
#include "utils/Logger.h"
#include "ViewManager.h"
#include "audio/AudioEngine.h"

using namespace Hatchet;


GroupItem::GroupItem( SourcesModel* model, SourceTreeItem* parent, const QString& text, int peerSortValue )
    : SourceTreeItem( model, parent, SourcesModel::Group, peerSortValue )
    , m_text( text )
    , m_defaultExpanded( true )
{
}


GroupItem::~GroupItem()
{
}


void
GroupItem::activate()
{
    emit toggleExpandRequest( this );
}


void
GroupItem::requestExpanding()
{
    emit expandRequest( this );
}


void
GroupItem::checkExpandedState()
{
    if ( m_defaultExpanded )
    {
        // only default expand once
        m_defaultExpanded = false;
        requestExpanding();
    }
}


QString
GroupItem::text() const
{
    return m_text;
}


bool
GroupItem::willAcceptDrag( const QMimeData* data ) const
{
    Q_UNUSED( data );
    return false;
}


QIcon
GroupItem::icon() const
{
    return QIcon();
}


bool
GroupItem::isBeingPlayed() const
{
    return false;
}


void
GroupItem::setDefaultExpanded( bool b )
{
    m_defaultExpanded = b;
}

