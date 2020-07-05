/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include <string.h>

#include <QtPlugin>
#include <QTimer>

#include "infosystem/InfoSystemWorker.h"
#include "Artist.h"
#include "Result.h"
#include "HatchetSettings.h"
#include "utils/LinkGenerator.h"
#include "utils/Logger.h"

#include "AdiumPlugin.h"
#include "Adium.h"

QString adium_beforeStatus;
QString adium_afterStatus;

static void setStatus(const QString &status)
{
    // The command that updates the status
    QString scriptqstr;
    scriptqstr.append(adium_beforeStatus);
    scriptqstr.append(status);
    scriptqstr.append(adium_afterStatus);

    const char* scriptstr = scriptqstr.toUtf8();
    script( scriptstr );
}

namespace Hatchet
{

namespace InfoSystem
{

AdiumPlugin::AdiumPlugin()
    : InfoPlugin()
{
    qDebug() << Q_FUNC_INFO;

    adium_beforeStatus = "if appIsRunning(\"Adium\") then\n";
    adium_beforeStatus.append("tell application \"Adium\"\n");
    adium_beforeStatus.append("set the status message of every account to \"");

    adium_afterStatus.append("\"\nend tell\n");
    adium_afterStatus.append("end if\n");
    adium_afterStatus.append("on appIsRunning(appName)\n");
    adium_afterStatus.append("tell application \"System Events\" to (name of processes) contains appName\n");
    adium_afterStatus.append("end appIsRunning\n");

    m_supportedPushTypes << InfoNowPlaying << InfoNowPaused << InfoNowResumed << InfoNowStopped;

    m_active = HatchetSettings::instance()->nowPlayingEnabled();

    connect( HatchetSettings::instance(), SIGNAL( changed() ),
                                             SLOT( settingsChanged() ), Qt::QueuedConnection );

    m_pauseTimer = new QTimer( this );
    m_pauseTimer->setSingleShot( true );
    connect( m_pauseTimer, SIGNAL( timeout() ),
             this, SLOT( clearStatus() ) );
}


AdiumPlugin::~AdiumPlugin()
{
    qDebug() << Q_FUNC_INFO;
    if( m_active )
      setStatus( "" );
}


void
AdiumPlugin::clearStatus()
{
    qDebug() << Q_FUNC_INFO;
    setStatus( "" );
}


void
AdiumPlugin::settingsChanged()
{
    m_active = HatchetSettings::instance()->nowPlayingEnabled();
}


void
AdiumPlugin::pushInfo( Hatchet::InfoSystem::InfoPushData pushData )
{
    qDebug() << Q_FUNC_INFO;

    if( !m_active )
        return;

    switch ( pushData.type )
    {
        case InfoNowPlaying:
          audioStarted( pushData.infoPair );
          break;
        case InfoNowPaused:
          audioPaused();
          return;
        case InfoNowResumed:
          audioResumed( pushData.infoPair );
          break;
        case InfoNowStopped:
          audioStopped();
          break;

        default:
          return;
    }

    // Stop the pause timer always, unless pausing of course
    m_pauseTimer->stop();
}


/** Audio state slots */
void
AdiumPlugin::audioStarted( const Hatchet::InfoSystem::PushInfoPair pushInfoPair )
{
    if ( !pushInfoPair.second.canConvert< QVariantMap >() )
        return;

    QVariantMap map = pushInfoPair.second.toMap();

    if ( map.contains( "private" ) && map[ "private" ] == HatchetSettings::FullyPrivate )
        return;

    if ( !map.contains( "trackinfo" ) || !map[ "trackinfo" ].canConvert< Hatchet::InfoSystem::InfoStringHash >() )
        return;

    InfoStringHash hash = map[ "trackinfo" ].value< Hatchet::InfoSystem::InfoStringHash >();

    if ( !hash.contains( "title" ) || !hash.contains( "artist" ) )
        return;

    m_currentTitle = hash["title"];
    m_currentArtist = hash["artist"];

    // Request a short URL
    ScriptJob* job = Utils::LinkGenerator::instance()->openLink( hash.value( "title" ), hash.value( "artist" ), hash.value( "album" ) );
    connect( job, SIGNAL( done( QVariantMap ) ), SLOT ( onQueryLinkReady( QVariantMap ) ) );
    job->start();
}


void
AdiumPlugin::onQueryLinkReady( const QVariantMap& data )
{

    m_currentLongUrl = data[ "url" ].toUrl();

    QUrl shortUrl = m_currentLongUrl;

    QString nowPlaying = "";
    nowPlaying.append( m_currentArtist );
    nowPlaying.append(" - ");
    nowPlaying.append( m_currentTitle );
    nowPlaying.replace( "\"", "\\\"" );  // Escape quotes, or Applescript gets confused

    // We failed to get the short URL, just update the status with the metadata
    if( ( m_currentLongUrl.toString() == "" ) )
    {
        setStatus( nowPlaying );
        return;
    }

    // Add the short URL
    nowPlaying.append( " " );
    nowPlaying.append( shortUrl.toEncoded() );
    setStatus( nowPlaying );

    sender()->deleteLater();
}


void
AdiumPlugin::audioFinished( const QVariant &input )
{
    //qDebug() << Q_FUNC_INFO;
}

void
AdiumPlugin::audioStopped()
{
    qDebug() << Q_FUNC_INFO;
    setStatus( "" );
}

void
AdiumPlugin::audioPaused()
{
    qDebug() << Q_FUNC_INFO;
    m_pauseTimer->start( 60 * 1000 );
}

void
AdiumPlugin::audioResumed( const Hatchet::InfoSystem::PushInfoPair pushInfoPair )
{
    qDebug() << Q_FUNC_INFO;
    audioStarted( pushInfoPair );
}

} //ns InfoSystem

} //ns Hatchet

Q_EXPORT_PLUGIN2( Hatchet::InfoSystem::InfoPlugin, Hatchet::InfoSystem::AdiumPlugin )
