/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Leo Franchi   <lfranchi@kde.org>
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

#include "ClientAuthValid.h"

#include "database/DatabaseImpl.h"
#include "HatchetSqlQuery.h"
#include "utils/Logger.h"
#include "Source.h"


namespace Hatchet
{

DatabaseCommand_ClientAuthValid::DatabaseCommand_ClientAuthValid( const QString& clientToken, QObject* parent )
    : DatabaseCommand( parent )
    , m_clientToken( clientToken )
{
}


void DatabaseCommand_ClientAuthValid::exec( DatabaseImpl* lib )
{
    HatchetSqlQuery q = lib->newquery();
    q.prepare( "SELECT name FROM http_client_auth WHERE token = ?" );
    q.addBindValue( m_clientToken );

    if ( q.exec() )
    {
        if ( q.next() )
        {
            QString name = q.value( 0 ).toString();
            emit authValid( m_clientToken, name, true );
        }
        else
        {
            emit authValid( m_clientToken, QString(), false );
        }
    }
    else
    {
        qWarning() << "Failed to query http auth table for client:" << m_clientToken;
    }
}

}
