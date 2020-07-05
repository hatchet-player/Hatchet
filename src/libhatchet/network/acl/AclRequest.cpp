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

#include "AclRequest_p.h"

namespace Hatchet {
namespace Network {
namespace ACL {


AclRequest::AclRequest( const QString& nodeid, const QString& username, Hatchet::ACLStatus::Type defaultStatus )
    : d_ptr( new AclRequestPrivate( this, nodeid, username, defaultStatus ) )
{
}


AclRequest::~AclRequest()
{
}


QString
AclRequest::nodeid() const
{
    Q_D( const AclRequest );
    return d->nodeid;
}


QString
AclRequest::username() const
{
    Q_D( const AclRequest );
    return d->username;
}


ACLStatus::Type
AclRequest::status() const
{
    Q_D( const AclRequest );
    return d->status;
}

void
AclRequest::emitDecision( ACLStatus::Type status )
{
    emit decision( status );
}


} // namespace ACL
} // namespace Network
} // namespace Hatchet
