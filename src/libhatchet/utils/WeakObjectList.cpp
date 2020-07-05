/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Uwe L. Korn <uwelk@xhochy.com>
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

#include "WeakObjectList.h"

namespace Hatchet {
namespace Utils {


void
WeakObjectListBase::remove( QObject* object )
{
    Q_UNUSED( object );
    // Nothing to do here
}


WeakObjectListBase::~WeakObjectListBase()
{
}


WeakObjectListPrivate::WeakObjectListPrivate( WeakObjectListBase* parent )
    : QObject( 0 )
    , m_parent( parent )
{
}


void
WeakObjectListPrivate::remove( QObject* object )
{
    m_parent->remove( object );
}

} // namespace Utils
} // namespace Hatchet
