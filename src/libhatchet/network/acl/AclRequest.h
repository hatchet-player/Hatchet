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

#ifndef HATCHET_NETWORK_ACL_ACLREQUEST_H
#define HATCHET_NETWORK_ACL_ACLREQUEST_H

#include "Typedefs.h"

#include <QObject>

namespace Hatchet {
namespace Network {
namespace ACL {

class AclRequestPrivate;

class AclRequest : public QObject
{
    Q_OBJECT
public:
    explicit AclRequest( const QString& nodeid, const QString& username, Hatchet::ACLStatus::Type defaultStatus = Hatchet::ACLStatus::NotFound );
    virtual ~AclRequest();

    QString nodeid() const;
    QString username() const;
    Hatchet::ACLStatus::Type status() const;

public slots:
    void emitDecision( Hatchet::ACLStatus::Type status );

signals:
    void decision( Hatchet::ACLStatus::Type status );

protected:
    QScopedPointer<AclRequestPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE( AclRequest )
};

} // namespace ACL
} // namespace Network
} // namespace Hatchet

#endif // HATCHET_NETWORK_ACL_ACLREQUEST_H
