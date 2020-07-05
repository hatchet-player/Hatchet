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

#include "LoadOps.h"

#include "database/DatabaseImpl.h"
#include "HatchetSqlQuery.h"
#include "Source.h"
#include "utils/Logger.h"

namespace Hatchet
{

void
DatabaseCommand_loadOps::exec( DatabaseImpl* dbi )
{
    QList< dbop_ptr > ops;

    if ( !m_since.isEmpty() )
    {
        HatchetSqlQuery query = dbi->newquery();
        query.prepare( QString( "SELECT id FROM oplog WHERE guid = ?" ) );
        query.addBindValue( m_since );
        query.exec();

        if ( !query.next() )
        {
            tLog() << "Unknown oplog guid, requested, not replying:" << m_since;
            Q_ASSERT( false );
            emit done( m_since, m_since, ops );
            return;
        }
    }

    HatchetSqlQuery query = dbi->newquery();
    query.prepare( QString(
                   "SELECT guid, command, json, compressed, singleton "
                   "FROM oplog "
                   "WHERE source %1 "
                   "AND id > coalesce((SELECT id FROM oplog WHERE guid = ?),0) "
                   "ORDER BY id ASC"
                   ).arg( source()->isLocal() ? "IS NULL" : QString( "= %1" ).arg( source()->id() ) )
                  );
    query.addBindValue( m_since );
    query.exec();

    QString lastguid = m_since;
    while( query.next() )
    {
        dbop_ptr op( new DBOp );
        op->guid = query.value( 0 ).toString();
        op->command = query.value( 1 ).toString();
        op->payload = query.value( 2 ).toByteArray();
        op->compressed = query.value( 3 ).toBool();
        op->singleton = query.value( 4 ).toBool();

        lastguid = op->guid;
        ops << op;
    }

//    qDebug() << "Loaded" << ops.length() << "ops from db";
    emit done( m_since, lastguid, ops );
}

}
