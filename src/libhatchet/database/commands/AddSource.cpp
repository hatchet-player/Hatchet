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

#include "AddSource.h"

#include <QSqlQuery>

#include "database/DatabaseImpl.h"
#include "utils/Logger.h"
#include "Source.h"

namespace Hatchet
{

DatabaseCommand_addSource::DatabaseCommand_addSource( const QString& username, const QString& fname, QObject* parent )
    : DatabaseCommand( parent )
    , m_username( username )
    , m_fname( fname )
{
}


void
DatabaseCommand_addSource::exec( DatabaseImpl* dbi )
{
    Q_ASSERT( !m_fname.isEmpty() );

    HatchetSqlQuery query = dbi->newquery();
    query.prepare( "SELECT id FROM source WHERE name = ?" );
    query.addBindValue( m_username );
    query.exec();

    if ( query.next() )
    {
        unsigned int id = query.value( 0 ).toInt();
        query.prepare( "UPDATE source SET isonline = 'true', friendlyname = ? WHERE id = ?" );
        query.addBindValue( m_fname );
        query.addBindValue( id );
        query.exec();
        emit done( id, m_fname );
        return;
    }

    query.prepare( "INSERT INTO source(name, friendlyname, isonline) VALUES(?,?,?)" );
    query.addBindValue( m_username );
    query.addBindValue( m_fname );
    query.addBindValue( "true" );
    query.exec();

    unsigned int id = query.lastInsertId().toUInt();
    tDebug() << "Inserted new source to DB, id:" << id << "friendlyname" << m_username;

    emit done( id, m_fname );
}

}
