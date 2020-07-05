/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *             2011, Dominik Schmidt <dev@dominik-schmidt.de>
 *             2010-2011, Leo Franchi <lfranchi@kde.org>
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

#include "sip/SipPlugin.h"

#include "utils/Logger.h"
#include "Source.h"
#include "sip/PeerInfo.h"


SipPlugin::SipPlugin() : QObject() {}
SipPlugin::~SipPlugin() {}

SipPlugin::SipPlugin( Hatchet::Accounts::Account *account, QObject* parent )
    : QObject( parent )
    , m_account( account )
{
    connect( account, SIGNAL( configurationChanged() ), SLOT( configurationChanged() ) );
}


QString
SipPlugin::pluginId() const
{
    return m_account->accountId();
}


const QString
SipPlugin::friendlyName() const
{
    return m_account->accountFriendlyName();
}


const QString
SipPlugin::serviceName() const
{
    return m_account->accountServiceName();
}

QString
SipPlugin::inviteString() const
{
    return QString();
}


QMenu*
SipPlugin::menu()
{
    return nullptr;
}


Hatchet::Accounts::Account*
SipPlugin::account() const
{
    return m_account;
}


const QList< Hatchet::peerinfo_ptr >
SipPlugin::peersOnline() const
{
    QList< Hatchet::peerinfo_ptr > result;

    foreach( const Hatchet::peerinfo_ptr& peerInfo, Hatchet::PeerInfo::getAll() )
    {
        if(peerInfo->sipPlugin() == this)
            result.append( peerInfo );
    }

    return result;
}


void SipPlugin::setAllPeersOffline()
{
    foreach( const Hatchet::peerinfo_ptr& peerInfo, peersOnline() )
    {
        peerInfo->setStatus( Hatchet::PeerInfo::Offline );
    }
}
