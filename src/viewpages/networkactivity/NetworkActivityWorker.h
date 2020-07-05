/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Uwe L. Korn <uwelk@xhochy.com>
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

#pragma once
#ifndef HATCHET_NETWORKACTIVITYWORKER_H
#define HATCHET_NETWORKACTIVITYWORKER_H

#include "Playlist.h"
#include "Typedefs.h"

#include <QObject>

namespace Hatchet
{

namespace Widgets
{

class NetworkActivityWorkerPrivate;

class NetworkActivityWorker : public QObject
{
    Q_OBJECT
public:
    explicit NetworkActivityWorker( QObject *parent = 0 );
    virtual ~NetworkActivityWorker();

public slots:
    void run();

signals:
    void trendingArtists( const QList< Hatchet::artist_ptr >& artists );
    void trendingTracks( const QList<Hatchet::track_ptr>& tracks );
    void hotPlaylists( const QList<Hatchet::playlist_ptr>& playlists );
    void finished();

protected:
    QScopedPointer<NetworkActivityWorkerPrivate> d_ptr;

private slots:
    void allPlaylistsReceived( const QHash< Hatchet::playlist_ptr, QStringList >& playlists );
    void allSourcesReceived( const QList< Hatchet::source_ptr >& sources );
    void playlistLoaded( Hatchet::PlaylistRevision );
    void playtime( const Hatchet::playlist_ptr& playlist , uint playtime );
    void trendingArtistsReceived( const QList< QPair< double,Hatchet::artist_ptr > >& tracks );
    void trendingTracksReceived( const QList< QPair< double,Hatchet::track_ptr > >& tracks );

private:
    Q_DECLARE_PRIVATE( NetworkActivityWorker )

    void checkDone();
    void checkHotPlaylistsDone();
};

} // namespace Widgets

} // namespace Hatchet

#endif // HATCHET_NETWORKACTIVITYWORKER_H
