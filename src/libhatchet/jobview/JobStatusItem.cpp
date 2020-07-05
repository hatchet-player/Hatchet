/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
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


#include "JobStatusItem.h"
#include <QTime>


JobStatusItem::JobStatusItem()
    : QObject()
    , m_createdOn( QDateTime::currentMSecsSinceEpoch() )
{
}


JobStatusItem::~JobStatusItem()
{
}


void
JobStatusItem::activated()
{
}


bool
JobStatusItem::allowMultiLine() const
{
    return false;
}


bool
JobStatusItem::collapseItem() const
{
    return false;
}


int
JobStatusItem::concurrentJobLimit() const
{
    return 0;
}


bool
JobStatusItem::hasCustomDelegate() const
{
    return false;
}


void
JobStatusItem::createDelegate( QObject* parent )
{
    Q_UNUSED( parent );
    return;
}


QStyledItemDelegate*
JobStatusItem::customDelegate() const
{
    return 0;
}
