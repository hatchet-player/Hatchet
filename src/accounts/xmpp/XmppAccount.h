/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Dominik Schmidt <dev@dominik-schmidt.de>
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2011, Leo Franchi <lfranchi@kde.org>
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

#ifndef XMPPACCOUNT_H
#define XMPPACCOUNT_H

#include "sip/XmppSip.h"
#include "accounts/AccountDllMacro.h"
#include "accounts/Account.h"
#include "accounts/AccountConfigWidget.h"

#define MYNAME "ACCOUNTJABBER"

class Ui_XmppConfigWidget;

namespace Hatchet
{

namespace Accounts
{

class ACCOUNTDLLEXPORT XmppAccountFactory : public AccountFactory
{
    Q_OBJECT
    Q_INTERFACES( Hatchet::Accounts::AccountFactory )
    Q_PLUGIN_METADATA( IID "org.hatchet-player.Player.AccountFactory" )

    // for settings access
    friend class XmppConfigWidget;
public:
    XmppAccountFactory() {}
    virtual ~XmppAccountFactory() {}

    QString prettyName() const { return "Jabber (XMPP)"; }
    QString description() const { return tr( "Login to connect to your Jabber/XMPP contacts that also use %applicationName." ); }
    QString factoryId() const { return "xmppaccount"; }
    QPixmap icon() const { return QPixmap( ":/xmpp-account/xmpp-icon.png" ); }
    AccountTypes types() const { return AccountTypes( SipType | StatusPushType ); }
    Account* createAccount( const QString& pluginId = QString() );
};

class ACCOUNTDLLEXPORT XmppAccount : public Account
{
    Q_OBJECT

public:
    XmppAccount( const QString &accountId );
    virtual ~XmppAccount();

    QPixmap icon() const;

    void authenticate();
    void deauthenticate();
    bool isAuthenticated() const;

    Hatchet::InfoSystem::InfoPluginPtr infoPlugin();

    SipPlugin* sipPlugin( bool create = true );

    AccountConfigWidget* configurationWidget() { return m_configWidget.data(); }
    QWidget* aclWidget() { return 0; }
    void saveConfig();

    virtual Hatchet::Accounts::Account::ConnectionState connectionState() const;

protected:
    QPointer< AccountConfigWidget > m_configWidget; // so the google wrapper can change the config dialog a bit
    QPointer< XmppSipPlugin > m_xmppSipPlugin;
    QPointer< Hatchet::InfoSystem::XmppInfoPlugin > m_xmppInfoPlugin;

    QPixmap m_onlinePixmap;
    QPixmap m_offlinePixmap;
};

};

};

#endif
