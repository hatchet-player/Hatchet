/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include "ViewPage.h"

#include "utils/Logger.h"

using namespace Hatchet;


ViewPage::~ViewPage()
{
}


bool
ViewPage::setFilter( const QString& filter )
{
    m_filter = filter;
    return false;
}


bool
ViewPage::willAcceptDrag( const QMimeData* data ) const
{
    Q_UNUSED( data );
    return false;
}


bool
ViewPage::dropMimeData( const QMimeData* data, Qt::DropAction action )
{
    Q_UNUSED( data );
    Q_UNUSED( action );
    return false;
}


bool
ViewPage::addPageItem() const {
    return true;
}


void
ViewPage::onItemDeleted()
{
    // no-op
}
