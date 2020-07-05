/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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


#ifndef COLLECTIONITEM_H
#define COLLECTIONITEM_H

#include "SourceTreeItem.h"
#include "libhatchet/collection/Collection.h"

class CollectionItem : public SourceTreeItem
{
    Q_OBJECT
public:
    explicit CollectionItem( SourcesModel* model, SourceTreeItem* parent, const Hatchet::collection_ptr& collection );
    virtual ~CollectionItem();

    virtual QString text() const override;
    virtual QIcon icon() const override;
    virtual int peerSortValue() const override;
    void setSortValue( int value );

    bool isBeingPlayed() const override;

    int trackCount() const;

public slots:
    virtual void activate() override;

private:
    int m_sortValue;
    QIcon m_icon;
    QString m_text;
    Hatchet::collection_ptr m_collection;

    /**
     * Reference to the ViewPage for the collection. Until the page is loaded
     * once on user request, this will be nullptr.
     */
    Hatchet::ViewPage* m_page;
};

#endif // COLLECTIONITEM_H
