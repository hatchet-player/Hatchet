/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2015, Dominik Schmidt <domme@tomahawk-player.org>
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

#include "ScriptInfoPluginFactory.h"

#include "SourceList.h"
#include "../ScriptAccount.h"

using namespace Hatchet;

void
ScriptInfoPluginFactory::addPlugin( const QSharedPointer< ScriptInfoPlugin >& infoPlugin ) const
{
    Hatchet::InfoSystem::InfoSystem::instance()->addInfoPlugin( infoPlugin );
}


void
ScriptInfoPluginFactory::removePlugin( const QSharedPointer< ScriptInfoPlugin >& infoPlugin ) const
{
    Hatchet::InfoSystem::InfoSystem::instance()->removeInfoPlugin( infoPlugin );
}


QSharedPointer< ScriptInfoPlugin >
ScriptInfoPluginFactory::createPlugin( const scriptobject_ptr& object, ScriptAccount* scriptAccount )
{
    // create infoplugin instance
    ScriptInfoPlugin* scriptInfoPlugin = new ScriptInfoPlugin( object, scriptAccount->name() );

    QSharedPointer< ScriptInfoPlugin > infoPlugin( scriptInfoPlugin );

    // move it to infosystem thread
    infoPlugin->moveToThread( Hatchet::InfoSystem::InfoSystem::instance()->workerThread().data() );

    return infoPlugin;
}
