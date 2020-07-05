/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QSignalMapper>
#include <QMenu>

#include "Typedefs.h"
#include "DllMacro.h"

namespace Hatchet
{

class DLLEXPORT ContextMenu : public QMenu
{
Q_OBJECT

public:
    enum MenuActions
    {
        ActionPlay =            1,
        ActionQueue =           2,
        ActionDelete =          4,
        ActionCopyLink =        8,
        ActionLove =            16,
        ActionStopAfter =       32,
        ActionPage =            64,
        ActionTrackPage =       128,
        ActionArtistPage =      256,
        ActionAlbumPage =       512,
        ActionEditMetadata =    1024,
        ActionPlaylist =        2048,
        ActionSend =            4096,
        ActionMarkListened =    8192,
        ActionDownload =        16384,
        ActionOpenFileManager = 32768
    };

    explicit ContextMenu( QWidget* parent = 0 );
    virtual ~ContextMenu();

    int supportedActions() const { return m_supportedActions; }
    void setSupportedActions( int actions ) { m_supportedActions = actions; }

    void setPlaylistInterface( const Hatchet::playlistinterface_ptr& plInterface );

    void setQuery( const Hatchet::query_ptr& query );
    void setQueries( const QList<Hatchet::query_ptr>& queries );

    void setArtist( const Hatchet::artist_ptr& artist );
    void setArtists( const QList<Hatchet::artist_ptr>& artists );

    void setAlbum( const Hatchet::album_ptr& album );
    void setAlbums( const QList<Hatchet::album_ptr>& albums );

    void clear();

    unsigned int itemCount() const;

signals:
    void triggered( int action );

private slots:
    void onTriggered( int action );
    void copyLink();
    void openPage( MenuActions action );
    void addToQueue();
    void addToPlaylist( int playlistIdx );
    void sendToSource( int sourceIdx );

    void onSocialActionsLoaded();

private:
    QSignalMapper* m_sigmap;
    QSignalMapper* m_playlists_sigmap;
    QSignalMapper* m_sources_sigmap;
    int m_supportedActions;

    QAction* m_loveAction;

    QList< Hatchet::playlist_ptr > m_playlists;
    QList< Hatchet::query_ptr > m_queries;
    QList< Hatchet::artist_ptr > m_artists;
    QList< Hatchet::album_ptr > m_albums;
    QList< Hatchet::source_ptr > m_sources;

    Hatchet::playlistinterface_ptr m_interface;
};

}; // ns

#endif
