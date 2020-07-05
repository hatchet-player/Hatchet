/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
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

#ifndef ZEROCONF_ACCOUNTS_H
#define ZEROCONF_ACCOUNTS_H

#include "HatchetPlugin.h"
#include "Zeroconf.h"
#include "accounts/Account.h"
#include "accounts/AccountDllMacro.h"

class SipPlugin;

namespace Hatchet
{
namespace Accounts
{

class ACCOUNTDLLEXPORT ZeroconfFactory : public AccountFactory
{
    Q_PLUGIN_METADATA( IID "org.hatchet-player.Player.AccountFactory" )
    Q_OBJECT
    Q_INTERFACES( Hatchet::Accounts::AccountFactory )

public:
    ZeroconfFactory();
    virtual ~ZeroconfFactory();

    QString factoryId() const override { return "zeroconfaccount"; }
    QString prettyName() const override { return tr( "Local Network" ); }
    QString description() const override { return tr( "Automatically connect to Hatchet users on the same local network." ); }
    bool isUnique() const override { return true; }
    AccountTypes types() const override { return AccountTypes( SipType ); }
    QPixmap icon() const override;

    Account* createAccount ( const QString& pluginId = QString() ) override;
};

class ACCOUNTDLLEXPORT ZeroconfAccount : public Account
{
    Q_OBJECT
public:
    ZeroconfAccount( const QString &accountId );
    virtual ~ZeroconfAccount();

    QPixmap icon() const override;

    void authenticate() override;
    void deauthenticate() override;
    bool isAuthenticated() const override;
    ConnectionState connectionState() const override;

    Hatchet::InfoSystem::InfoPluginPtr infoPlugin() override { return Hatchet::InfoSystem::InfoPluginPtr(); }
    SipPlugin* sipPlugin( bool create = true ) override;

    AccountConfigWidget* configurationWidget() override { return nullptr; }
    QWidget* aclWidget() override { return nullptr; }

private:
    QPointer< ZeroconfPlugin > m_sipPlugin;
};

}
}

#endif
