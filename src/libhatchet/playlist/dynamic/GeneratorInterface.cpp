/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
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

#include "playlist/dynamic/GeneratorInterface.h"

#include "utils/Logger.h"
#include "Source.h"


Hatchet::GeneratorInterface::GeneratorInterface( QObject* parent )
    : QObject( parent )
{
}


Hatchet::GeneratorInterface::~GeneratorInterface()
{
}


QList< Hatchet::dyncontrol_ptr >
Hatchet::GeneratorInterface::controls()
{
//     if( m_controls.isEmpty() ) { // return a default control (so the user can add more)
//         return QList< Hatchet::dyncontrol_ptr >() << createControl();
//     }

    return m_controls;
}


QPixmap
Hatchet::GeneratorInterface::logo()
{
    return QPixmap();
}


void
Hatchet::GeneratorInterface::addControl( const Hatchet::dyncontrol_ptr& control )
{
    m_controls << control;
}


void
Hatchet::GeneratorInterface::clearControls()
{
    m_controls.clear();
}


void
Hatchet::GeneratorInterface::setControls( const QList< Hatchet::dyncontrol_ptr >& controls )
{
    m_controls = controls;
}


void
Hatchet::GeneratorInterface::removeControl( const Hatchet::dyncontrol_ptr& control )
{
    m_controls.removeAll( control );
}


Hatchet::dyncontrol_ptr
Hatchet::GeneratorInterface::createControl( const QString& type )
{
    Q_UNUSED( type );
    Q_ASSERT( false );
    return dyncontrol_ptr();
}
