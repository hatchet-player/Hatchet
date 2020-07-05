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

#include "PlaybackCharts.h"

#include "utils/HatchetUtils.h"
#include "utils/Logger.h"

#include "Artist.h"
#include "database/DatabaseImpl.h"
#include "PlaylistEntry.h"
#include "Source.h"

#include <QSqlQuery>

namespace Hatchet
{

DatabaseCommand_PlaybackCharts::DatabaseCommand_PlaybackCharts( const Hatchet::source_ptr& source, QObject* parent )
    : DatabaseCommand( parent )
    , m_amount( 0 )
{
    setSource( source );
}


DatabaseCommand_PlaybackCharts::~DatabaseCommand_PlaybackCharts()
{
}


void
DatabaseCommand_PlaybackCharts::exec( DatabaseImpl* dbi )
{
    HatchetSqlQuery query = dbi->newquery();
    QString sourceToken;

    if ( source() )
        sourceToken = QString( "AND playback_log.source %1" ).arg( source()->isLocal() ? "IS NULL" : QString( "= %1" ).arg( source()->id() ) );

    QString sql = QString(
            "SELECT artist.id, artist.name, COUNT(*) AS counter "
            "FROM playback_log, artist, track "
            "WHERE playback_log.track = track.id "
            "AND artist.id = track.artist "
            "%1 "
            "GROUP BY artist.id "
            "ORDER BY counter DESC "
            "%2"
            ).arg( sourceToken )
             .arg( m_amount > 0 ? QString( "LIMIT 0, %1" ).arg( m_amount ) : QString() );

    query.prepare( sql );
    query.exec();

    QList<Hatchet::artist_ptr> al;
    while ( query.next() )
    {
        Hatchet::artist_ptr artist = Hatchet::Artist::get( query.value( 0 ).toUInt(), query.value( 1 ).toString() );
        al << artist;
    }

    emit artists( al );
    emit done();
}

}
