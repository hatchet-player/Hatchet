/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2011, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2013, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef RECENTLYPLAYEDPLAYLISTSMODEL_H
#define RECENTLYPLAYEDPLAYLISTSMODEL_H

#include <QModelIndex>

#include "Playlist.h"
#include "Source.h"

class RecentlyPlayedPlaylistsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemRoles
    { ArtistRole = Qt::UserRole, TrackCountRole, PlaylistRole, PlaylistTypeRole, DynamicPlaylistRole };
    enum PlaylistTypes
    { StaticPlaylist, AutoPlaylist, Station };

    explicit RecentlyPlayedPlaylistsModel( QObject* parent = 0 );

    void setMaxPlaylists( unsigned int max ) { m_maxPlaylists = max; }

    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;

signals:
    void emptinessChanged( bool isEmpty );

public slots:
    void sourceOnline();

private slots:
    void playlistChanged( Hatchet::playlistinterface_ptr );
    void onSourceAdded( const Hatchet::source_ptr& source );
    void onPlaylistsRemoved( QList<Hatchet::playlist_ptr> );
    void loadFromSettings();

    void plAdded( const QString& plguid, int sourceId );
    void playlistRevisionLoaded();

private:
    QList< Hatchet::playlist_ptr > m_recplaylists;
    QHash< QString, Hatchet::playlist_ptr > m_cached;
    mutable QHash< Hatchet::playlist_ptr, QString > m_artists;

    unsigned int m_maxPlaylists;
    bool m_waitingForSome;
};

#endif // RECENTLYPLAYEDPLAYLISTSMODEL_H
