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
#ifndef NETWORKACTIVITYWORKER_P_H
#define NETWORKACTIVITYWORKER_P_H

#include "NetworkActivityWorker.h"

#include <QStack>

namespace Hatchet
{

namespace Widgets
{

class NetworkActivityWorkerPrivate
{
public:
    NetworkActivityWorkerPrivate( NetworkActivityWorker* q )
        : q_ptr( q )
        , trendingArtistsDone( false )
        , trendingTracksDone( false )
        , hotPlaylistsDone( false )
        , playlistsToLoad( 0 )
        , playtimesToLoad( 0 )
        , trackStatsToLoad( 0 )
    {
    }

    NetworkActivityWorker* q_ptr;
    Q_DECLARE_PUBLIC( NetworkActivityWorker )
private:
    bool trendingArtistsDone;
    bool trendingTracksDone;

    bool hotPlaylistsDone;
    QList< Hatchet::playlist_ptr > hotPlaylists;
    QHash< Hatchet::playlist_ptr, QStringList > playlists;
    uint playlistsToLoad;
    uint playtimesToLoad;
    uint sourcesToLoad;
    uint trackStatsToLoad;
    QStack<playlist_ptr> playlistStack;
    QMultiMap<uint, playlist_ptr> playlistCount;
};

} // namespace Widgets

} // namespace Hatchet

#endif // NETWORKACTIVITYWORKER_P_H
