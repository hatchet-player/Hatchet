/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012, Dominik Schmidt <domme@tomahawk-player.org>
 *   Copyright 2012, Jeff Mitchell <jeff@tomahawk-player.org>
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


#include "XmppInfoPlugin.h"

#include "utils/LinkGenerator.h"
#include "sip/XmppSip.h"
#include "utils/Logger.h"
#include "HatchetSettings.h"


// remove now playing status after PAUSE_TIMEOUT seconds
static const int PAUSE_TIMEOUT = 10;

Hatchet::InfoSystem::XmppInfoPlugin::XmppInfoPlugin( XmppSipPlugin* sipPlugin )
    : m_sipPlugin( sipPlugin )
    , m_pauseTimer( this )
{
    Q_ASSERT( sipPlugin->m_client );

    m_supportedPushTypes << InfoNowPlaying << InfoNowPaused << InfoNowResumed << InfoNowStopped;

    m_pauseTimer.setSingleShot( true );
    connect( &m_pauseTimer, SIGNAL( timeout() ),
             this, SLOT( audioStopped() ) );
}


Hatchet::InfoSystem::XmppInfoPlugin::~XmppInfoPlugin()
{
}


void
Hatchet::InfoSystem::XmppInfoPlugin::init()
{
    if ( QThread::currentThread() != Hatchet::InfoSystem::InfoSystem::instance()->workerThread().data() )
    {
        QMetaObject::invokeMethod( this, "init", Qt::QueuedConnection );
        return;
    }

    if ( m_sipPlugin.isNull() )
        return;

    connect( this, SIGNAL( publishTune( QUrl, Hatchet::InfoSystem::InfoStringHash ) ), m_sipPlugin.data(), SLOT( publishTune( QUrl, Hatchet::InfoSystem::InfoStringHash ) ), Qt::QueuedConnection );
}


const QString
Hatchet::InfoSystem::XmppInfoPlugin::friendlyName() const
{
    return "xmpp";
}


void
Hatchet::InfoSystem::XmppInfoPlugin::pushInfo( Hatchet::InfoSystem::InfoPushData pushData )
{
    switch ( pushData.type )
    {
        case InfoNowPlaying:
        case InfoNowResumed:
            m_pauseTimer.stop();
            audioStarted( pushData.infoPair );
            break;
        case InfoNowPaused:
            m_pauseTimer.start( PAUSE_TIMEOUT * 1000 );
            audioPaused();
            break;
        case InfoNowStopped:
            m_pauseTimer.stop();
            audioStopped();
            break;

        default:
            return;
    }
}


void
Hatchet::InfoSystem::XmppInfoPlugin::audioStarted( const Hatchet::InfoSystem::PushInfoPair &pushInfoPair )
{
    if ( !pushInfoPair.second.canConvert< QVariantMap >() )
    {
        tDebug() << Q_FUNC_INFO << "Failed to convert data to a QVariantMap";
        return;
    }

    QVariantMap map = pushInfoPair.second.toMap();
    if ( map.contains( "private" ) && map[ "private" ] == HatchetSettings::FullyPrivate )
    {
        emit publishTune( QUrl(), Hatchet::InfoSystem::InfoStringHash() );
        return;
    }

    if ( !map.contains( "trackinfo" ) || !map[ "trackinfo" ].canConvert< Hatchet::InfoSystem::InfoStringHash >() )
    {
        tDebug() << Q_FUNC_INFO << "did not find an infostringhash";
        return;
    }

    Hatchet::InfoSystem::InfoStringHash info = map[ "trackinfo" ].value< Hatchet::InfoSystem::InfoStringHash >();

    ScriptJob* job = Utils::LinkGenerator::instance()->openLink( info.value( "title" ), info.value( "artist" ), info.value( "album" ) );
    connect( job, SIGNAL( done( QVariantMap ) ), SLOT( onQueryLinkReady( QVariantMap ) ) );
    job->setProperty( "infoStringHash", QVariant::fromValue( info ) );
    job->start();
}


void
Hatchet::InfoSystem::XmppInfoPlugin::onQueryLinkReady( const QVariantMap& data )
{
    emit publishTune( data[ "url" ].toUrl(), sender()->property("infoStringHash").value< Hatchet::InfoSystem::InfoStringHash >() );

    sender()->deleteLater();
}


void
Hatchet::InfoSystem::XmppInfoPlugin::audioPaused()
{
}


void
Hatchet::InfoSystem::XmppInfoPlugin::audioStopped()
{
    emit publishTune( QUrl(), Hatchet::InfoSystem::InfoStringHash() );
}


void
Hatchet::InfoSystem::XmppInfoPlugin::getInfo(Hatchet::InfoSystem::InfoRequestData requestData)
{
    Q_UNUSED( requestData );
}


void
Hatchet::InfoSystem::XmppInfoPlugin::notInCacheSlot(const Hatchet::InfoSystem::InfoStringHash criteria, Hatchet::InfoSystem::InfoRequestData requestData)
{
    Q_UNUSED( criteria );
    Q_UNUSED( requestData );
}
