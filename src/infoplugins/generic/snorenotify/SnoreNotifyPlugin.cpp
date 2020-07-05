/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013-2015, Hannah von Reth <vonreth@kde.org>
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

#include "SnoreNotifyPlugin.h"

#include "HatchetSettings.h"
#include "utils/HatchetUtils.h"
#include "utils/Logger.h"
#include "utils/HatchetUtilsGui.h"

#include "HatchetVersion.h"

#include <libsnore/application.h>
#include <libsnore/notification/icon.h>

#include <QApplication>

#include <QImage>
#include <QPixmap>


namespace Hatchet
{

namespace InfoSystem
{

SnoreNotifyPlugin::SnoreNotifyPlugin()
    : InfoPlugin(),
      m_defaultIcon( RESPATH "icons/hatchet-icon-512x512.png" )
{
    tDebug( LOGVERBOSE ) << Q_FUNC_INFO;
    m_supportedPushTypes << InfoNotifyUser << InfoNowPlaying << InfoTrackUnresolved << InfoNowStopped << InfoInboxReceived;

    Snore::SnoreCore &snore = Snore::SnoreCore::instance();
    snore.loadPlugins( Snore::SnorePlugin::Backend | Snore::SnorePlugin::SecondaryBackend );
    snore.setDefaultSettingsValue( {QStringLiteral("Silent"), Snore::LocalSetting}, true );

    m_application = Snore::Application( qApp->applicationName(), m_defaultIcon );
    m_application.hints().setValue( "use-markup", true );
    m_application.hints().setValue( "windows-app-id", HATCHET_APPLICATION_PACKAGE_NAME );
    m_application.hints().setValue( "desktop-entry", HATCHET_APPLICATION_NAME );

    addAlert( InfoNotifyUser, tr( "Notify User" ) );
    addAlert( InfoNowPlaying, tr( "Now Playing" ) );
    addAlert( InfoTrackUnresolved, tr( "Unresolved track" ) );
    addAlert( InfoNowStopped, tr( "Playback Stopped" ) );
    addAlert( InfoInboxReceived, tr( "You received a Song recommendation" ) );

    snore.registerApplication( m_application );
    snore.setDefaultApplication( m_application );

    connect( &snore, SIGNAL( actionInvoked( Snore::Notification ) ), this, SLOT( slotActionInvoked( Snore::Notification ) ) );
}


SnoreNotifyPlugin::~SnoreNotifyPlugin()
{
    tDebug( LOGVERBOSE ) << Q_FUNC_INFO;

    Snore::SnoreCore::instance().deregisterApplication( m_application );
}

void
SnoreNotifyPlugin::pushInfo( Hatchet::InfoSystem::InfoPushData pushData )
{
    tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "showing notification:" << HatchetSettings::instance()->songChangeNotificationEnabled();
    if ( !HatchetSettings::instance()->songChangeNotificationEnabled() )
        return;


    switch ( pushData.type )
    {
        case Hatchet::InfoSystem::InfoTrackUnresolved:
            notifyUser( Hatchet::InfoSystem::InfoTrackUnresolved, tr( "The current track could not be resolved. %applicationName will pick back up with the next resolvable track from this source." ), m_defaultIcon );
            return;

        case Hatchet::InfoSystem::InfoNotifyUser:
            notifyUser( Hatchet::InfoSystem::InfoNotifyUser,pushData.infoPair.second.toString(), m_defaultIcon );
            return;

        case Hatchet::InfoSystem::InfoNowStopped:
            notifyUser( Hatchet::InfoSystem::InfoNowStopped, tr( "%applicationName stopped playback." ), m_defaultIcon );
            return;

        case Hatchet::InfoSystem::InfoNowPlaying:
            nowPlaying( pushData.infoPair.second );
            return;

        case Hatchet::InfoSystem::InfoInboxReceived:
            inboxReceived( pushData.infoPair.second );
            return;

        default:
            return;
    }

}

void
SnoreNotifyPlugin::slotActionInvoked( Snore::Notification n )
{
    Q_UNUSED(n)
    HatchetUtils::bringToFront();
}


void
SnoreNotifyPlugin::notifyUser( Hatchet::InfoSystem::InfoType type, const QString& messageText, Snore::Icon icon  )
{
    const Snore::Alert &alert = m_alerts[ type ];
    Snore::Notification n( m_application , alert, alert.name(), messageText, icon );
    Snore::SnoreCore::instance().broadcastNotification( n );
    tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "showing notification:" << messageText;
}

void
SnoreNotifyPlugin::addAlert( Hatchet::InfoSystem::InfoType type, const QString &title )
{
    Snore::Alert alert( title, m_defaultIcon );
    m_application.addAlert( alert );
    m_alerts[ type ] = alert;
}

void
SnoreNotifyPlugin::nowPlaying( const QVariant& input )
{

    tDebug( LOGVERBOSE ) << Q_FUNC_INFO;
    if ( !input.canConvert< QVariantMap >() )
        return;

    QVariantMap map = input.toMap();
    if ( !map.contains( "trackinfo" ) || !map[ "trackinfo" ].canConvert< Hatchet::InfoSystem::InfoStringHash >() )
        return;

    InfoStringHash hash = map[ "trackinfo" ].value< Hatchet::InfoSystem::InfoStringHash >();
    if ( !hash.contains( "title" ) || !hash.contains( "artist" ) || !hash.contains( "album" ) )
        return;

    QString messageText;
    // If the window manager supports notification styling then use it.

    // Remark: If using xml-based markup in notifications, the supplied strings need to be escaped.
    QString album;
    if ( !hash[ "album" ].isEmpty() )
        album = QString( "<br><i>%1</i> %2" ).arg( tr( "on", "'on' is followed by an album name" ) ).arg( hash[ "album" ].toHtmlEscaped() );

    messageText = tr( "%1%4 %2%3.", "%1 is a title, %2 is an artist and %3 is replaced by either the previous message or nothing, %4 is the preposition used to link track and artist ('by' in english)" )
            .arg( hash[ "title" ].toHtmlEscaped() )
            .arg( hash[ "artist" ].toHtmlEscaped() )
            .arg( album )
            .arg( QString( "<br><i>%1</i>" ).arg( tr( "by", "preposition to link track and artist" ) ) );

    // Dirty hack(TM) so that KNotify/QLabel recognizes the message as Rich Text
    messageText = QString( "<i></i>%1" ).arg( messageText );

    tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "sending message" << messageText;

    // If there is a cover availble use it, else use Hatchet logo as default.
    Snore::Icon image = m_defaultIcon;
    if ( map.contains( "cover" ) && map[ "cover" ].canConvert< QImage >() )
    {
        image = Snore::Icon( QPixmap::fromImage( map[ "cover" ].value< QImage >() ) );
        tDebug( LOGVERBOSE ) << Q_FUNC_INFO << image;
    }
    notifyUser( InfoNowPlaying, messageText, image );
}



void
SnoreNotifyPlugin::inboxReceived( const QVariant& input )
{
    tDebug( LOGVERBOSE ) << Q_FUNC_INFO;
    if ( !input.canConvert< QVariantMap >() )
        return;

    QVariantMap map = input.toMap();

    if ( !map.contains( "trackinfo" ) || !map[ "trackinfo" ].canConvert< Hatchet::InfoSystem::InfoStringHash >() )
        return;
    if ( !map.contains( "sourceinfo" ) || !map[ "sourceinfo" ].canConvert< Hatchet::InfoSystem::InfoStringHash >() )
        return;

    InfoStringHash hash = map[ "trackinfo" ].value< Hatchet::InfoSystem::InfoStringHash >();
    if ( !hash.contains( "title" ) || !hash.contains( "artist" ) )
        return;

    InfoStringHash src = map[ "sourceinfo" ].value< Hatchet::InfoSystem::InfoStringHash >();
    if ( !src.contains( "friendlyname" ) )
        return;

    QString messageText;
    // Remark: If using xml-based markup in notifications, the supplied strings need to be escaped.
    messageText = tr( "%1 sent you\n%2%4 %3.", "%1 is a nickname, %2 is a title, %3 is an artist, %4 is the preposition used to link track and artist ('by' in english)" )
            .arg( src["friendlyname"].toHtmlEscaped() )
            .arg( hash[ "title" ].toHtmlEscaped() )
            .arg( hash[ "artist" ].toHtmlEscaped() )
            .arg( QString( "\n<i>%1</i>" ).arg( tr( "by", "preposition to link track and artist" ) ) );

    // Dirty hack(TM) so that KNotify/QLabel recognizes the message as Rich Text
    messageText = QString( "<i></i>%1" ).arg( messageText );

    Snore::Icon icon( RESPATH "images/inbox-512x512.png" );
    notifyUser( Hatchet::InfoSystem::InfoInboxReceived, messageText, icon );
}


} //ns InfoSystem

} //ns Hatchet

Q_EXPORT_PLUGIN2( Hatchet::InfoSystem::InfoPlugin, Hatchet::InfoSystem::SnoreNotifyPlugin )
