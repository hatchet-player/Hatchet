/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
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


#ifndef SOURCESMODEL_H
#define SOURCESMODEL_H

#include "Typedefs.h"
#include "Source.h"
#include "ViewPage.h"

#include <QModelIndex>
#include <QStringList>
#include <QList>
#include <QAction>

class QMimeData;

class SourceTreeItem;
class GroupItem;

namespace Hatchet {
    class Source;
    class Playlist;
}

class SourcesModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum RowType {
        Invalid = -1,
        Divider = 9,

        Source = 0,
        Group = 8,

        Category = 1,
        CategoryAdd = 2,

        StaticPlaylist = 3,
        AutomaticPlaylist = 4,
        Station = 5,

        GenericPage = 6,
        TemporaryPage = 7,
        LovedTracksPage = 10,
        DeletablePage = 15,
        RemovablePage = 16,

        Collection = 14,
        ScriptCollection = 11,

        Inbox = 12,
        Queue = 13
    };

    enum CategoryType {
        PlaylistsCategory = 0,
        StationsCategory = 1
    };

    enum Roles {
        SourceTreeItemRole      = Qt::UserRole + 10,
        SourceTreeItemTypeRole  = Qt::UserRole + 11,
        SortRole                = Qt::UserRole + 12,
        IDRole                  = Qt::UserRole + 13,
        LatchedOnRole           = Qt::UserRole + 14,
        LatchedRealtimeRole     = Qt::UserRole + 15,
        CustomActionRole        = Qt::UserRole + 16 // QList< QAction* >
    };

    SourcesModel( QObject* parent = nullptr );
    virtual ~SourcesModel();

    static QString rowTypeToString( RowType type );

    // reimplemented from QAIM
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex& child) const;
    virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);

    virtual QStringList mimeTypes() const;
    virtual QMimeData* mimeData(const QModelIndexList& indexes) const;
    virtual bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent);
    virtual Qt::DropActions supportedDropActions() const;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const;

    void appendGroups();

    void appendItem( const Hatchet::source_ptr& source );
    bool removeItem( const Hatchet::source_ptr& source );

    void linkSourceItemToPage( SourceTreeItem* item, Hatchet::ViewPage* p );
    void removeSourceItemLink( SourceTreeItem* item );

    QModelIndex indexFromItem( SourceTreeItem* item ) const;

    QList< Hatchet::source_ptr > sourcesWithViewPage() const;

public slots:
    void loadSources();

    void itemUpdated();
    void onItemRowsAddedBegin( int first, int last );
    void onItemRowsAddedDone();
    void onItemRowsRemovedBegin( int first, int last );
    void onItemRowsRemovedDone();

    void viewPageActivated( Hatchet::ViewPage* );

    void itemSelectRequest( SourceTreeItem* item );
    void itemExpandRequest( SourceTreeItem* item );
    void itemToggleExpandRequest( SourceTreeItem* item );

signals:
    void selectRequest( const QPersistentModelIndex& idx );
    void expandRequest( const QPersistentModelIndex& idx );
    void toggleExpandRequest( const QPersistentModelIndex& idx );

private slots:
    void onSourcesAdded( const QList<Hatchet::source_ptr>& sources );
    void onSourceAdded( const Hatchet::source_ptr& source );
    void onSourceRemoved( const Hatchet::source_ptr& source );

    void onScriptCollectionAdded( const Hatchet::collection_ptr& collection );
    void onScriptCollectionRemoved( const Hatchet::collection_ptr& collection );

    void onViewPageRemoved( Hatchet::ViewPage* p );

    Hatchet::ViewPage* scriptCollectionClicked( const Hatchet::collection_ptr& collection );
    Hatchet::ViewPage* getScriptCollectionPage( const Hatchet::collection_ptr& collection ) const;

    void onWidgetDestroyed( QWidget* w );

    /*
     *  name is the internal name in the ViewManager
     */
    void appendPageItem( const QString& name, Hatchet::ViewPage* page, int sortValue );

private:
    SourceTreeItem* itemFromIndex( const QModelIndex& idx ) const;
    int rowForItem( SourceTreeItem* item ) const;
    SourceTreeItem* activatePlaylistPage( Hatchet::ViewPage* p, SourceTreeItem* i );

    SourceTreeItem* m_rootItem;
    GroupItem* m_browse;
    GroupItem* m_collectionsGroup;
    GroupItem* m_myMusicGroup;
    GroupItem* m_cloudGroup;

    QList< Hatchet::source_ptr > m_sourcesWithViewPage;
    QHash< Hatchet::source_ptr, SourceTreeItem* > m_sourcesWithViewPageItems;
    QHash< Hatchet::collection_ptr, SourceTreeItem* > m_scriptCollections;
    QHash< Hatchet::collection_ptr, Hatchet::ViewPage* > m_scriptCollectionPages;

    QHash< Hatchet::ViewPage*, SourceTreeItem* > m_sourceTreeLinks;
    Hatchet::ViewPage* m_viewPageDelayedCacheItem;
};

Q_DECLARE_METATYPE( QList< QAction* > )

#endif // SOURCESMODEL_H
