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

#include "playlist/dynamic/GeneratorFactory.h"
#include "playlist/dynamic/GeneratorInterface.h"

#include "utils/Logger.h"
#include "Source.h"

using namespace Hatchet;


QHash< QString, GeneratorFactoryInterface* > GeneratorFactory::s_factories = QHash< QString, GeneratorFactoryInterface* >();

geninterface_ptr
GeneratorFactory::create ( const QString& type )
{
    if( type.isEmpty() && !s_factories.isEmpty() ) // default, return first
        return geninterface_ptr( s_factories.begin().value()->create() );

    if( !s_factories.contains( type ) )
        return geninterface_ptr();

    return geninterface_ptr( s_factories.value( type )->create() );
}


dyncontrol_ptr
GeneratorFactory::createControl( const QString& generatorType, const QString& controlType )
{
    if( generatorType.isEmpty() || !s_factories.contains( generatorType ) )
        return dyncontrol_ptr();

    return s_factories.value( generatorType )->createControl( controlType );
}


void
GeneratorFactory::registerFactory ( const QString& type, GeneratorFactoryInterface* interface )
{
    s_factories.insert( type, interface );
}


QStringList
GeneratorFactory::types()
{
    return s_factories.keys();
}


QStringList
GeneratorFactory::typeSelectors( const QString& type )
{
    if( !s_factories.contains( type ) )
        return QStringList();

    return s_factories.value( type )->typeSelectors();
}
