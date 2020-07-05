/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
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

#include "ArtistStats.h"

#include "utils/Logger.h"

#include "Artist.h"
#include "database/DatabaseImpl.h"
#include "PlaylistEntry.h"
#include "SourceList.h"


using namespace Hatchet;


DatabaseCommand_ArtistStats::DatabaseCommand_ArtistStats( const artist_ptr& artist, QObject* parent )
    : DatabaseCommand( parent )
    , m_artist( artist )
{
}


void
DatabaseCommand_ArtistStats::exec( DatabaseImpl* dbi )
{
    HatchetSqlQuery query = dbi->newquery();

    query.prepare( "SELECT COUNT(*) AS counter, artist.id "
                   "FROM playback_log, track, artist "
                   "WHERE playback_log.source IS NULL AND track.id = playback_log.track AND artist.id = track.artist "
                   "GROUP BY track.artist "
                   "ORDER BY counter DESC" );
    query.exec();

    unsigned int plays = 0;
    unsigned int chartPos = 0;
    unsigned int chartCount = 0;
    const unsigned int artistId = m_artist->id();

    QHash< QString, unsigned int > charts;
    while ( query.next() )
    {
        if ( query.value( 0 ).toUInt() < 2 )
            break;

        chartCount++;
        if ( chartPos == 0 && query.value( 1 ).toUInt() == artistId )
        {
            chartPos = chartCount;
            plays = query.value( 0 ).toUInt();
        }
    }

    if ( chartPos == 0 )
        chartPos = chartCount;

    emit done( plays, chartPos, chartCount );
}
