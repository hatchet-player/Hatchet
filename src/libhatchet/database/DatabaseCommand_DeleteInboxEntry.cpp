/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Teo Mrnjavac <teo@kde.org>
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

#include "DatabaseCommand_DeleteInboxEntry.h"
#include "DatabaseImpl.h"
#include "Query.h"
#include "Track.h"


namespace Hatchet
{

DatabaseCommand_DeleteInboxEntry::DatabaseCommand_DeleteInboxEntry( const Hatchet::query_ptr& query,
                                                                    QObject* parent )
    : DatabaseCommand( parent )
    , m_query( query )
{
}


void
DatabaseCommand_DeleteInboxEntry::exec( DatabaseImpl* dbi )
{
    HatchetSqlQuery query = dbi->newquery();

    Q_ASSERT( !m_query.isNull() );

    if ( m_query->queryTrack()->track().isEmpty() || m_query->queryTrack()->artist().isEmpty() )
    {
        emit done();
        return;
    }

    query.prepare(
                "DELETE FROM social_attributes "
                "WHERE social_attributes.k = ? AND social_attributes.id = ( "
                    "SELECT id FROM track "
                    "WHERE track.name = ? AND track.artist = ( "
                        "SELECT id FROM artist WHERE artist.name = ? "
                    ") "
                ")" );
    query.addBindValue( "Inbox" );
    query.addBindValue( m_query->queryTrack()->track() );
    query.addBindValue( m_query->queryTrack()->artist() );

    query.exec();

    emit done();
}

}
