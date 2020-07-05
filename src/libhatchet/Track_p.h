/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2013, Teo Mrnjavac <teo@kde.org>
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
#ifndef TRACK_P_H
#define TRACK_P_H

#include "Track.h"

namespace Hatchet {

class TrackPrivate
{
public:
    TrackPrivate( Track* q, const QString& _album, const QString& _albumArtist, int _duration, const QString& _composer, unsigned int _albumpos, unsigned int _discnumber )
        : q_ptr( q )
        , composer( _composer )
        , album( _album )
        , albumArtist( _albumArtist )
        , duration( _duration )
        , albumpos( _albumpos )
        , discnumber( _discnumber )
    {
    }

    Track* q_ptr;
    Q_DECLARE_PUBLIC( Track )

private:
    QString composer;
    QString album;
    QString albumArtist;
    QString composerSortname;
    QString albumSortname;

    int duration;
    uint albumpos;
    uint discnumber;

    mutable Hatchet::artist_ptr artistPtr;
    mutable Hatchet::artist_ptr albumArtistPtr;
    mutable Hatchet::album_ptr albumPtr;
    mutable Hatchet::artist_ptr composerPtr;

    mutable trackdata_ptr trackData;

    query_wptr query;
    QWeakPointer< Hatchet::Track > ownRef;
};

} // namespace Hatchet

#endif // TRACK_P_H
