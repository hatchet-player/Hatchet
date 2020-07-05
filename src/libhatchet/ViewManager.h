/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "Artist.h"
#include "ViewPage.h"
#include "ViewPagePlugin.h"
#include "collection/Collection.h"
#include "PlaylistInterface.h"
#include "playlist/QueueView.h"

#include <QObject>
#include <QHash>
#include <QStackedWidget>

#include "DllMacro.h"

#include <functional>

class AlbumModel;
class GridView;
class AlbumInfoWidget;
class ArtistInfoWidget;
class CollectionModel;
class PlaylistViewPage;
class CollectionViewPage;
class PlaylistModel;
class TrackProxyModel;
class TrackModel;
class TreeProxyModel;
class TreeModel;
class TrackView;
class SourceInfoWidget;
class TrackInfoWidget;
class QPushButton;
class InboxModel;

namespace Hatchet
{
    class DynamicWidget;
}

class DLLEXPORT ViewManager : public QObject
{
Q_OBJECT

public:
    static ViewManager* instance();

    explicit ViewManager( QObject* parent = 0 );
    virtual ~ViewManager();

    QWidget* widget() const { return m_widget; }

    QueueView* queue() const { return m_queue; }
    void setQueue( QueueView* queue ) { m_queue = queue; }

    Hatchet::playlistinterface_ptr currentPlaylistInterface() const;
    Hatchet::ViewPage* currentPage() const;
    Hatchet::ViewPage* pageForInterface( Hatchet::playlistinterface_ptr plInterface ) const;

    Hatchet::ViewPage* show( Hatchet::ViewPage* page );

    Hatchet::ViewPage* inboxWidget() const;
    Hatchet::ViewPage* dynamicPageWidget( const QString& pageName ) const;

    InboxModel* inboxModel();

    /// Get the view page for the given item. Not pretty...
    Hatchet::ViewPage* pageForPlaylist( const Hatchet::playlist_ptr& pl ) const;
    Hatchet::ViewPage* pageForDynPlaylist( const Hatchet::dynplaylist_ptr& pl ) const;

    /// Get a playlist (or dynamic playlist ) from a ViewPage* if the page is PlaylistViewPage or DynamicWidget.
    /// Lives here but used by SourcesModel
    Hatchet::playlist_ptr playlistForPage( Hatchet::ViewPage* ) const;

    // only use this is you need to create a playlist and show it directly and want it to be
    // linked to the sidebar. call it right after creating the playlist
    PlaylistViewPage* createPageForPlaylist( const Hatchet::playlist_ptr& playlist );

    PlaylistViewPage* createPageForList( const QString& title, const QList< Hatchet::query_ptr >& queries );

    void addDynamicPage( Hatchet::ViewPagePlugin* viewPage, const QString& pageName = QString() );

signals:
    void playClicked();
    void pauseClicked();

    void tempPageActivated( Hatchet::ViewPage* );
    void viewPageActivated( Hatchet::ViewPage* );
    void viewPageAboutToBeDestroyed( Hatchet::ViewPage* );
    void viewPageDestroyed();

    void historyBackAvailable( bool avail );
    void historyForwardAvailable( bool avail );

    void viewPageAdded( const QString& pageName, Hatchet::ViewPage* page, int sortValue );

public slots:
    Hatchet::ViewPage* showInboxPage();
    Hatchet::ViewPage* showQueuePage();

//    void addDynamicPage( const QString& pageName, const QString& text, const QIcon& icon, function< Hatchet::ViewPage*() > instanceLoader, int sortValue = 0 );
    Hatchet::ViewPage* showDynamicPage( const QString& pageName );

    void showCurrentTrack();

    // Returns the shown viewpage
    Hatchet::ViewPage* show( const Hatchet::playlist_ptr& playlist );
    Hatchet::ViewPage* show( const Hatchet::dynplaylist_ptr& playlist );
    Hatchet::ViewPage* show( const Hatchet::artist_ptr& artist );
    Hatchet::ViewPage* show( const Hatchet::album_ptr& album );
    Hatchet::ViewPage* show( const Hatchet::query_ptr& query );
    Hatchet::ViewPage* show( const Hatchet::collection_ptr& collection );
    Hatchet::ViewPage* show( const Hatchet::source_ptr& source );

    void historyBack();
    void historyForward();

    QList< Hatchet::ViewPage* > allPages() const;
    QList< Hatchet::ViewPage* > historyPages() const;
    void destroyPage( Hatchet::ViewPage* page );
    bool destroyCurrentPage();

    void playlistInterfaceChanged( Hatchet::playlistinterface_ptr );

private slots:
    void onWidgetDestroyed( QWidget* widget );

private:
    void setPage( Hatchet::ViewPage* page, bool trackHistory = true );

    Hatchet::playlist_ptr playlistForInterface( Hatchet::playlistinterface_ptr plInterface ) const;
    Hatchet::dynplaylist_ptr dynamicPlaylistForInterface( Hatchet::playlistinterface_ptr plInterface ) const;

    QWidget* m_widget;
    QStackedWidget* m_stack;

    QueueView* m_queue;
    Hatchet::ViewPage* m_inboxWidget;
    InboxModel* m_inboxModel;

    QHash< QString, Hatchet::ViewPage* > m_dynamicPages;
    QHash< QString, QPointer< Hatchet::ViewPagePlugin > > m_dynamicPagePlugins;
    QHash< QString, std::function< Hatchet::ViewPage*() > > m_dynamicPagesInstanceLoaders;

    QHash< Hatchet::dynplaylist_ptr, QPointer<Hatchet::DynamicWidget> > m_dynamicWidgets;
    QHash< Hatchet::collection_ptr, QPointer<CollectionViewPage> > m_collectionViews;
    QHash< Hatchet::artist_ptr, QPointer<ArtistInfoWidget> > m_artistViews;
    QHash< Hatchet::album_ptr, QPointer<AlbumInfoWidget> > m_albumViews;
    QHash< Hatchet::query_ptr, QPointer<TrackInfoWidget> > m_trackViews;
    QHash< Hatchet::playlist_ptr, QPointer<PlaylistViewPage> > m_playlistViews;
    QHash< Hatchet::source_ptr, QPointer<SourceInfoWidget> > m_sourceViews;

    QList<Hatchet::ViewPage*> m_pageHistoryBack;
    QList<Hatchet::ViewPage*> m_pageHistoryFwd;
    Hatchet::ViewPage* m_currentPage;

    Hatchet::collection_ptr m_currentCollection;

    static ViewManager* s_instance;
};

#endif // VIEWMANAGER_H
