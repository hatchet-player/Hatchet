/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include "PlaybackHistory.h"

#include <QSqlQuery>

#include "database/DatabaseImpl.h"
#include "SourceList.h"

#include "utils/Logger.h"


namespace Hatchet
{

void
DatabaseCommand_PlaybackHistory::exec( DatabaseImpl* dbi )
{
    HatchetSqlQuery query = dbi->newquery();
    QString whereToken( "WHERE 1" );

    if ( !source().isNull() )
    {
        whereToken += QString( " AND source %1" ).arg( source()->isLocal() ? "IS NULL" : QString( "= %1" ).arg( source()->id() ) );
    }
    if ( m_dateFrom.year() > 1900 && m_dateTo.year() > 1900 )
    {
        whereToken += QString( " AND playtime >= %1 AND playtime <= %2" )
                         .arg( QDateTime( m_dateFrom ).toUTC().toTime_t() )
                         .arg( QDateTime( m_dateTo.addDays( 1 ) ).toUTC().toTime_t() );
    }

    QString sql = QString(
            "SELECT track, playtime, secs_played, source "
            "FROM playback_log "
            "%1 "
            "ORDER BY playtime DESC "
            "%2" ).arg( whereToken )
                  .arg( m_amount > 0 ? QString( "LIMIT 0, %1" ).arg( m_amount ) : QString() );

    query.prepare( sql );
    query.exec();

    QList<Hatchet::track_ptr> tl;
    QList<Hatchet::PlaybackLog> logs;
    while ( query.next() )
    {
        HatchetSqlQuery query_track = dbi->newquery();

        QString sql = QString(
                "SELECT track.name, artist.name "
                "FROM track, artist "
                "WHERE artist.id = track.artist "
                "AND track.id = %1"
                ).arg( query.value( 0 ).toUInt() );

        query_track.prepare( sql );
        query_track.exec();

        if ( query_track.next() )
        {
            Hatchet::track_ptr track = Hatchet::Track::get( query_track.value( 1 ).toString(), query_track.value( 0 ).toString(), QString() );
            if ( !track )
                continue;

            Hatchet::PlaybackLog log;
            log.timestamp = query.value( 1 ).toUInt();
            log.secsPlayed = query.value( 2 ).toUInt();
            log.source = SourceList::instance()->get( query.value( 3 ).toUInt() );

            logs << log;
            tl << track;
        }
    }

    emit tracks( tl, logs );
}

}
