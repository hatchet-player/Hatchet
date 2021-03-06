/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2013-2014, Uwe L. Korn <uwelk@xhochy.com>
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

// Marked portions of this file are subject to the following copyright:
/*
 * Copyright (C) 2009 by Aurélien Gâteau <aurelien.gateau@canonical.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "FdoNotifyPlugin.h"

#include "ImageConverter.h"
#include "FreedesktopNotificationsProxy.h"

#include "HatchetSettings.h"

#include "utils/HatchetUtils.h"
#include "utils/Logger.h"
#include "utils/HatchetUtilsGui.h"

#include "HatchetVersion.h"

#include <QDBusConnection>
#include <QDBusPendingCallWatcher>
#include <QImage>

namespace Hatchet
{

namespace InfoSystem
{

QString escapeHtml( const QString& str ) {
    return str.toHtmlEscaped();
}

FdoNotifyPlugin::FdoNotifyPlugin()
    : InfoPlugin()
    , m_nowPlayingId( 0 )
    , m_wmSupportsBodyMarkup( false )
{
    tDebug( LOGVERBOSE ) << Q_FUNC_INFO;
    m_supportedPushTypes << InfoNotifyUser << InfoNowPlaying << InfoNowResumed << InfoTrackUnresolved << InfoNowStopped << InfoInboxReceived;

    // Query the window manager for its capabilties in styling notifications.
    notifications_interface = new org::freedesktop::Notifications( "org.freedesktop.Notifications", "/org/freedesktop/Notifications",
                                                                   QDBusConnection::sessionBus(), this );
    QDBusPendingReply<QStringList> reply = notifications_interface->GetCapabilities();

    QDBusPendingCallWatcher* watcher = new QDBusPendingCallWatcher( reply, this );
    connect( watcher, SIGNAL( finished( QDBusPendingCallWatcher* ) ), SLOT( dbusCapabilitiesReplyReceived( QDBusPendingCallWatcher* ) ) );
}


FdoNotifyPlugin::~FdoNotifyPlugin()
{
    tDebug( LOGVERBOSE ) << Q_FUNC_INFO;
}


void
FdoNotifyPlugin::dbusCapabilitiesReplyReceived( QDBusPendingCallWatcher* watcher )
{
    QDBusMessage reply = watcher->reply();
    watcher->deleteLater();

    if ( reply.type() == QDBusMessage::ErrorMessage )
    {
        tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "Failed to request capabilities of notifications";
    }

    const QStringList& capability_list = reply.arguments().first().toStringList();
    m_wmSupportsBodyMarkup = capability_list.contains( "body-markup" );
}


void
FdoNotifyPlugin::pushInfo( Hatchet::InfoSystem::InfoPushData pushData )
{
    tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "showing notification:" << HatchetSettings::instance()->songChangeNotificationEnabled();

    if ( !HatchetSettings::instance()->songChangeNotificationEnabled() )
        return;

    QVariant inputData = pushData.infoPair.second;

    switch ( pushData.type )
    {
        case Hatchet::InfoSystem::InfoTrackUnresolved:
            notifyUser( tr( "The current track could not be resolved. %applicationName will pick back up with the next resolvable track from this source." ) );
            return;

        case Hatchet::InfoSystem::InfoNotifyUser:
            notifyUser( pushData.infoPair.second.toString() );
            return;

        case Hatchet::InfoSystem::InfoNowStopped:
            notifyUser( tr( "%applicationName is stopped." ) );
            return;

        case Hatchet::InfoSystem::InfoNowPlaying:
        case Hatchet::InfoSystem::InfoNowResumed:
            nowPlaying( pushData.infoPair.second );
            return;

        case Hatchet::InfoSystem::InfoInboxReceived:
            inboxReceived( pushData.infoPair.second );
            return;

        default:
            return;
    }

}


/**
 * Determine a consistent size for the cover image depending on the default font height
 */
int
FdoNotifyPlugin::getNotificationIconHeight()
{
     return 6 * HatchetUtils::defaultFontHeight();
}


void
FdoNotifyPlugin::notifyUser( const QString& messageText )
{
    QVariantMap hints;
    hints["desktop-entry"] = QString( "hatchet" );
    hints[ "image_data" ] = ImageConverter::variantForImage( QImage( RESPATH "icons/hatchet-icon-512x512.png" ).scaledToHeight( getNotificationIconHeight() ) );
    notifications_interface->Notify(
        "Hatchet",    // app_name
        0,             // notification_id
        "",            // app_icon
        "Hatchet",    // summary
        messageText,   // body
        QStringList(), // actions
        hints,         // hints
        -1             // expire_timeout
    );
}


void FdoNotifyPlugin::inboxReceived( const QVariant& input )
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
    // If the window manager supports notification styling then use it.
    if ( m_wmSupportsBodyMarkup )
    {
        // Remark: If using xml-based markup in notifications, the supplied strings need to be escaped.
        messageText = tr( "%1 sent you\n%2%4 %3.", "%1 is a nickname, %2 is a title, %3 is an artist, %4 is the preposition used to link track and artist ('by' in english)" )
                        .arg( escapeHtml( src["friendlyname"] ) )
                        .arg( escapeHtml( hash[ "title" ] ) )
                        .arg( escapeHtml( hash[ "artist" ] ) )
                        .arg( QString( "\n<i>%1</i>" ).arg( tr( "by", "preposition to link track and artist" ) ) );

        // Dirty hack(TM) so that KNotify/QLabel recognizes the message as Rich Text
        messageText = QString( "<i></i>%1" ).arg( messageText );
    }
    else
    {
        messageText = tr( "%1 sent you \"%2\" by %3.", "%1 is a nickname, %2 is a title, %3 is an artist" )
                        .arg( src["friendlyname"] )
                        .arg( hash[ "title" ] )
                        .arg( hash[ "artist" ] );
    }

    tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "sending message" << messageText;

    QVariantMap hints;
    hints["desktop-entry"] = QString( "hatchet" );

    // Convert image to QVariant and scale to a consistent size.
    hints[ "image_data" ] = ImageConverter::variantForImage( QImage( RESPATH "images/inbox-512x512.png" ).scaledToHeight( getNotificationIconHeight() ) );
    notifications_interface->Notify(
        "Hatchet",                  // app_name
        m_nowPlayingId,              // notification_id
        "",                          // app_icon
        "Hatchet - Track received", // summary
        messageText,                 // body
        QStringList(),               // actions
        hints,                       // hints
        -1                           // expire_timeout
    );
}


void
FdoNotifyPlugin::nowPlaying( const QVariant& input )
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
    if ( m_wmSupportsBodyMarkup )
    {
        // Remark: If using xml-based markup in notifications, the supplied strings need to be escaped.
        QString album;
        if ( !hash[ "album" ].isEmpty() )
            album = QString( "\n<i>%1</i> %2" )
                    .arg( tr( "on", "'on' is followed by an album name" ) )
                    .arg( escapeHtml( hash[ "album" ] ) );

        messageText = tr( "%1%4 %2%3.", "%1 is a title, %2 is an artist and %3 is replaced by either the previous message or nothing, %4 is the preposition used to link track and artist ('by' in english)" )
                        .arg( escapeHtml( hash[ "title" ] ) )
                        .arg( escapeHtml( hash[ "artist" ] ) )
                        .arg( album )
                        .arg( QString( "\n<i>%1</i>" ).arg( tr( "by", "preposition to link track and artist" ) ) );

        // Dirty hack(TM) so that KNotify/QLabel recognizes the message as Rich Text
        messageText = QString( "<i></i>%1" ).arg( messageText );
    }
    else
    {
        QString album;
        if ( !hash[ "album" ].isEmpty() )
            album = QString( " %1" ).arg( tr( "on \"%1\"", "%1 is an album name" ).arg( hash[ "album" ] ) );

        messageText = tr( "\"%1\" by %2%3.", "%1 is a title, %2 is an artist and %3 is replaced by either the previous message or nothing" )
                        .arg( hash[ "title" ] )
                        .arg( hash[ "artist" ] )
                        .arg( album );
    }

    tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "sending message" << messageText;

    QVariantMap hints;
    hints["desktop-entry"] = QString( "hatchet" );

    // If there is a cover availble use it, else use Hatchet logo as default.
    QImage image;
    if ( map.contains( "coveruri" ) && map[ "coveruri" ].canConvert< QString >() )
        image = QImage( map[ "coveruri" ].toString(), "PNG" );
    else
        image = QImage( RESPATH "icons/hatchet-icon-512x512.png" );
    // Convert image to QVariant and scale to a consistent size.
    hints[ "image_data" ] = ImageConverter::variantForImage( image.scaledToHeight( getNotificationIconHeight() ) );


    QDBusPendingReply<> reply = notifications_interface->Notify(
        HATCHET_APPLICATION_NAME,      // app_name
        m_nowPlayingId,                 // notification_id
        "",                             // app_icon
        tr( "%applicationName - Now Playing" ), // summary
        messageText,                    // body
        QStringList(),                  // actions
        hints,                          // hints
        -1                              // expire_timeout
    );

    QDBusPendingCallWatcher* watcher = new QDBusPendingCallWatcher( reply, this );
    connect( watcher, SIGNAL( finished( QDBusPendingCallWatcher* ) ), SLOT( dbusPlayingReplyReceived( QDBusPendingCallWatcher* ) ) );
}


/**
 * Handle the DBus reply triggered by FdoNotifyPlugin::nowPlaying
 */
void
FdoNotifyPlugin::dbusPlayingReplyReceived( QDBusPendingCallWatcher* watcher )
{
    QDBusMessage reply = watcher->reply();
    watcher->deleteLater();

    if ( reply.type() == QDBusMessage::ErrorMessage )
    {
        tLog(LOGVERBOSE) << "Failed to grab media keys" << reply.errorName() << reply.errorMessage();
        return;
    }

    const QVariantList& list = reply.arguments();
    if ( !list.isEmpty() )
        m_nowPlayingId = list.first().toInt();
}

} //ns InfoSystem

} //ns Hatchet

Q_EXPORT_PLUGIN2( Hatchet::InfoSystem::InfoPlugin, Hatchet::InfoSystem::FdoNotifyPlugin )
