/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef HISTORY_ITEM_H
#define HISTORY_ITEM_H

#include "GroupItem.h"

class TemporaryPageItem;
class GenericPageItem;
class CategoryItem;

namespace Hatchet
{
    class ViewPage;
}

class HistoryItem : public GroupItem
{
    Q_OBJECT
public:
    HistoryItem( SourcesModel* model, SourceTreeItem* parent, const QString& text, int peerSortValue = 0 );
    virtual ~HistoryItem();

private slots:
    void tempPageActivated( Hatchet::ViewPage* );
    void temporaryPageDestroyed();

private:
    QList< TemporaryPageItem* > m_tempItems;

private:
};

#endif
