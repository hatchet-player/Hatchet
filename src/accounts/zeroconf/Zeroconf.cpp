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

#include "Zeroconf.h"

#include "HatchetSettings.h"
#include "utils/Logger.h"
#include "ZeroconfAccount.h"
#include "Source.h"
#include "sip/PeerInfo.h"
#include "sip/SipInfo.h"
#include "network/ControlConnection.h"

#include <QtPlugin>
#include <QTimer>

using namespace Hatchet;
using namespace Accounts;

#define MYNAME "zeroconf"

ZeroconfPlugin::ZeroconfPlugin ( ZeroconfAccount* parent )
    : SipPlugin( parent )
    , m_zeroconf( nullptr )
    , m_state( Account::Disconnected )
    , m_cachedNodes()
{
    m_advertisementTimer.setInterval( 60000 );
    m_advertisementTimer.setSingleShot( false );
    connect( &m_advertisementTimer, SIGNAL( timeout() ), SLOT( advertise() ) );
}


ZeroconfPlugin::~ZeroconfPlugin()
{
}

const QString
ZeroconfPlugin::serviceName() const
{
    return QString( MYNAME );
}


const QString
ZeroconfPlugin::friendlyName() const
{
    return QString( MYNAME );
}


Account::ConnectionState
ZeroconfPlugin::connectionState() const
{
    return m_state;
}


void
ZeroconfPlugin::connectPlugin()
{
    delete m_zeroconf;
    m_zeroconf = new HatchetZeroconf( Servent::instance()->port(), this );
    QObject::connect( m_zeroconf, SIGNAL( hatchetHostFound( QString, int, QString, QString ) ),
                                    SLOT( lanHostFound( QString, int, QString, QString ) ) );

    advertise();
    m_state = Account::Connected;

    foreach( const QStringList& nodeSet, m_cachedNodes )
    {
        lanHostFound( nodeSet[0], nodeSet[1].toInt(), nodeSet[2], nodeSet[3]);
    }
    m_cachedNodes.clear();

    m_advertisementTimer.start();
}


void
ZeroconfPlugin::disconnectPlugin()
{
    m_advertisementTimer.stop();
    m_state = Account::Disconnected;

    delete m_zeroconf;
    m_zeroconf = nullptr;

    setAllPeersOffline();
}


void
ZeroconfPlugin::advertise()
{
    m_zeroconf->advertise();
}


void
ZeroconfPlugin::lanHostFound( const QString& host, int port, const QString& name, const QString& nodeid )
{
    if ( sender() != m_zeroconf )
        return;

    qDebug() << "Found LAN host:" << host << port << nodeid;

    if ( m_state != Account::Connected )
    {
        qDebug() << "Not online, so not connecting.";
        QStringList nodeSet;
        nodeSet << host << QString::number( port ) << name << nodeid;
        m_cachedNodes.append( nodeSet );
        return;
    }

    SipInfo sipInfo;
    sipInfo.setHost( host );
    sipInfo.setPort( port );
    sipInfo.setNodeId( nodeid );
    sipInfo.setKey( "whitelist" );
    sipInfo.setVisible( true );

    Hatchet::peerinfo_ptr peerInfo = Hatchet::PeerInfo::get( this, host, Hatchet::PeerInfo::AutoCreate );
    QList<SipInfo> sipInfos = QList<SipInfo>();
    sipInfos.append( sipInfo );
    peerInfo->setSipInfos( sipInfos );
    peerInfo->setContactId( host );
    peerInfo->setFriendlyName( name );
    peerInfo->setType( PeerInfo::Local );
    peerInfo->setStatus( PeerInfo::Online );
}


