/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef HATCHET_ACLREGISTRYIMPL_H
#define HATCHET_ACLREGISTRYIMPL_H

#include "network/acl/AclRegistry.h"
#include "HeadlessCheck.h"

#include <queue>

class ACLJobItem;

class ACLRegistryImpl : public ACLRegistry
{
    Q_OBJECT

public:

    ACLRegistryImpl( QObject *parent = nullptr );
    virtual ~ACLRegistryImpl();

public slots:
    /**
     * @brief Checks if peer is authorized; optionally, can authorize peer with given type if not found
     *
     * @param dbid DBID of peer
     * @param globalType Global ACL to store if peer not found; if ACLRegistry::NotFound, does not store the peer Defaults to ACLRegistry::NotFound.
     * @param username If not empty, will store the given username along with the new ACL value. Defaults to QString().
     * @return Hatchet::ACLStatus::Type
     **/
    Hatchet::ACLStatus::Type isAuthorizedUser( const QString &dbid,
                                                const QString &username,
                                                Hatchet::ACLStatus::Type globalType = Hatchet::ACLStatus::NotFound,
                                                bool skipEmission = false ) override;
    void wipeEntries() override;

protected:
    void load() override;
    void save() override;

    void getUserDecision( ACLRegistry::User user, const QString &username );

private slots:
    void userDecision( ACLRegistry::User user );
    void queueNextJob();

private:
    std::queue< ACLJobItem* > m_jobQueue;
    int m_jobCount;
};

#endif // HATCHET_ACLREGISTRYIMPL_H
