/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2011, Leo Franchi <lfranchi@kde.org>
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

#ifndef ZEROCONF_H
#define ZEROCONF_H

#include "sip/SipPlugin.h"
#include "accounts/Account.h"
#include "HatchetZeroconf.h"

#include "accounts/AccountDllMacro.h"

#include <QtCore/QTimer>

namespace Hatchet
{
namespace Accounts
{

class ZeroconfAccount;


class ACCOUNTDLLEXPORT ZeroconfPlugin : public SipPlugin
{
    Q_OBJECT

public:
    ZeroconfPlugin( ZeroconfAccount* acc );

    virtual ~ZeroconfPlugin();

    const QString friendlyName() const override;
    const QString serviceName() const override;
    bool isValid() const override { return true; }
    void checkSettings() override {}
    void configurationChanged() override {}

    Account::ConnectionState connectionState() const;

public slots:
    void connectPlugin() override;
    void disconnectPlugin() override;

    void advertise();

    virtual void sendSipInfos( const Hatchet::peerinfo_ptr& /* receiver */, const QList<SipInfo>& /* info */ ) override {}
    void broadcastMsg( const QString& ) {}
    bool addContact( const QString&, AddContactOptions, const QString& ) override { return false; }

private slots:
    void lanHostFound( const QString& host, int port, const QString& name, const QString& nodeid );

private:
    HatchetZeroconf* m_zeroconf;
    Account::ConnectionState m_state;
    QVector<QStringList> m_cachedNodes;
    QTimer m_advertisementTimer;
};

}
}

#endif
