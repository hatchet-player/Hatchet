/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2013,      Teo Mrnjavac <teo@kde.org>
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

#ifndef SOURCE_ITEM_H
#define SOURCE_ITEM_H

#include "SourceTreeItem.h"

class TemporaryPageItem;
class GenericPageItem;
class CategoryItem;

namespace Hatchet
{
    class ViewPage;
}

class SourceItem : public SourceTreeItem
{
    Q_OBJECT
public:
    SourceItem( SourcesModel* model, SourceTreeItem* parent, const Hatchet::source_ptr& source );

    virtual QString text() const;
    virtual QString tooltip() const;
    virtual QIcon icon() const;
    virtual QPixmap pixmap( const QSize& size = QSize( 0, 0 ) ) const;
    virtual int peerSortValue() const;
    virtual int IDValue() const;

    virtual bool localLatchedOn() const;
    virtual Hatchet::PlaylistModes::LatchMode localLatchMode() const;

    Hatchet::source_ptr source() const;

    CategoryItem* stationsCategory() const;
    CategoryItem* playlistsCategory() const;
    void setStationsCategory( CategoryItem* item );
    void setPlaylistsCategory( CategoryItem* item );

    virtual bool willAcceptDrag( const QMimeData* data ) const;
    virtual bool dropMimeData( const QMimeData* data, Qt::DropAction action );
    virtual DropTypes supportedDropTypes( const QMimeData* data ) const;
    virtual Qt::ItemFlags flags() const;

public slots:
    virtual void activate();

private slots:
    void onPlaylistsAdded( const QList<Hatchet::playlist_ptr>& playlists );
    void onPlaylistDeleted( const Hatchet::playlist_ptr& playlists );
    void onAutoPlaylistsAdded( const QList<Hatchet::dynplaylist_ptr>& playlists );
    void onAutoPlaylistDeleted( const Hatchet::dynplaylist_ptr& playlists );
    void onStationsAdded( const QList<Hatchet::dynplaylist_ptr>& stations );
    void onStationDeleted( const Hatchet::dynplaylist_ptr& stations );

    void latchedOn( const Hatchet::source_ptr&, const Hatchet::source_ptr& );
    void latchedOff( const Hatchet::source_ptr&, const Hatchet::source_ptr& );
    void latchModeChanged( Hatchet::PlaylistModes::LatchMode mode );

    void onCollectionAdded( const Hatchet::collection_ptr& ); //never call from ctor because of begin/endRowsAdded!
    void onCollectionRemoved( const Hatchet::collection_ptr& );

    void requestExpanding();

    Hatchet::ViewPage* sourceInfoClicked();
    Hatchet::ViewPage* getSourceInfoPage() const;

    Hatchet::ViewPage* collectionClicked( const Hatchet::collection_ptr& collection );
    Hatchet::ViewPage* getCollectionPage( const Hatchet::collection_ptr& collection ) const;

    Hatchet::ViewPage* latestAdditionsClicked();
    Hatchet::ViewPage* getLatestAdditionsPage() const;

    Hatchet::ViewPage* recentPlaysClicked();
    Hatchet::ViewPage* getRecentPlaysPage() const;

    void onTracksDropped( const QList< Hatchet::query_ptr >& queries );

private:
    void playlistsAddedInternal( SourceTreeItem* parent, const QList< Hatchet::dynplaylist_ptr >& playlists );
    template< typename T >
    void playlistDeletedInternal( SourceTreeItem* parent, const T& playlists );
    void performAddCollectionItem( const Hatchet::collection_ptr& collection );

    Hatchet::source_ptr m_source;
    CategoryItem* m_playlists;
    CategoryItem* m_stations;

    bool m_latchedOn;
    Hatchet::source_ptr m_latchedOnTo;

    QMap< Hatchet::collection_ptr, SourceTreeItem* > m_collectionItems;
    QMap< Hatchet::collection_ptr, Hatchet::ViewPage* > m_collectionPages;

    GenericPageItem* m_sourceInfoItem;
    GenericPageItem* m_latestAdditionsItem;
    GenericPageItem* m_recentPlaysItem;

    Hatchet::ViewPage* m_sourceInfoPage;
    Hatchet::ViewPage* m_latestAdditionsPage;
    Hatchet::ViewPage* m_recentPlaysPage;
};


#endif
