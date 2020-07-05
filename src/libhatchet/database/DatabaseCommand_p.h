/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2013,      Uwe L. Korn <uwelk@xhochy.com>
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

#ifndef DATABASECOMMAND_P_H
#define DATABASECOMMAND_P_H

#include "database/DatabaseCommand.h"

namespace Hatchet
{

class DatabaseCommandPrivate
{
public:
    explicit DatabaseCommandPrivate( DatabaseCommand* q )
        : q_ptr( q )
        , state( DatabaseCommand::PENDING )
    {
    }

    explicit DatabaseCommandPrivate( DatabaseCommand* q, const Hatchet::source_ptr& src )
        : q_ptr( q )
        , source( src )
        , state( DatabaseCommand::PENDING )
    {
    }

    Q_DECLARE_PUBLIC( DatabaseCommand )
    DatabaseCommand* q_ptr;

private:
    Hatchet::source_ptr source;
    DatabaseCommand::State state;
    mutable QString guid;
    QVariant data;
    QWeakPointer< Hatchet::DatabaseCommand > ownRef;

};

} // Hatchet

#endif // DATABASECOMMAND_P_H
