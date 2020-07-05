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

#include "LoadAllSources.h"

#include "database/DatabaseImpl.h"
#include "Source.h"

using namespace Hatchet;


DatabaseCommand_LoadAllSources::DatabaseCommand_LoadAllSources( QObject* parent )
    : DatabaseCommand( parent )
{
}


void
DatabaseCommand_LoadAllSources::exec( DatabaseImpl* dbi )
{
    HatchetSqlQuery query = dbi->newquery();

    query.exec( QString( "SELECT id, name, friendlyname, lastop "
                         "FROM source" ) );

    QList<source_ptr> sources;
    while ( query.next() )
    {
        source_ptr src( new Source( query.value( 0 ).toUInt(), query.value( 1 ).toString() ) );
        src->setDbFriendlyName( query.value( 2 ).toString() );
        src->setLastCmdGuid( query.value( 3 ).toString() );
        sources << src;
    }

    emit done( sources );
}

