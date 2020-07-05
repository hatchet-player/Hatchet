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

#include "WeakObjectHash.h"


Hatchet::Utils::WeakObjectHashPrivate::WeakObjectHashPrivate(Hatchet::Utils::WeakObjectHashBase *parent)
    : QObject( 0 )
    , m_parent( parent )
{
}


void
Hatchet::Utils::WeakObjectHashPrivate::remove( const QString& key )
{
    m_parent->remove( key );
}


void
Hatchet::Utils::WeakObjectHashBase::remove( const QString& key )
{
    Q_UNUSED( key );
    // Does nothing but needs to be implemented for linking
}


Hatchet::Utils::WeakObjectHashBase::~WeakObjectHashBase()
{
}


