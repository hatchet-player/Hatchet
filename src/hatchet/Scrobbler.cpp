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

#include "Scrobbler.h"

#include "Artist.h"
#include "Album.h"
#include "Source.h"
#include "Typedefs.h"
#include "HatchetSettings.h"
#include "Track.h"
#include "audio/AudioEngine.h"
#include "infosystem/InfoSystem.h"

#include "utils/Logger.h"

#include <QDir>
#include <QSettings>
#include <QCryptographicHash>

static QString s_scInfoIdentifier = QString( "SCROBBLER" );


Scrobbler::Scrobbler( QObject* parent )
    : QObject( parent )
    , m_reachedScrobblePoint( false )
{
    connect( AudioEngine::instance(), SIGNAL( timerSeconds( unsigned int ) ),
                                        SLOT( engineTick( unsigned int ) ), Qt::QueuedConnection );

    connect( Hatchet::InfoSystem::InfoSystem::instance(),
             SIGNAL( info( Hatchet::InfoSystem::InfoRequestData, QVariant ) ),
             SLOT( infoSystemInfo( Hatchet::InfoSystem::InfoRequestData, QVariant ) ) );

    connect( AudioEngine::instance(), SIGNAL( started( const Hatchet::result_ptr ) ),
             SLOT( trackStarted( const Hatchet::result_ptr ) ), Qt::QueuedConnection );

    connect( AudioEngine::instance(), SIGNAL( paused() ),
             SLOT( trackPaused() ), Qt::QueuedConnection );

    connect( AudioEngine::instance(), SIGNAL( resumed() ),
             SLOT( trackResumed() ), Qt::QueuedConnection );

    connect( AudioEngine::instance(), SIGNAL( stopped() ),
             SLOT( trackStopped() ), Qt::QueuedConnection );

    connect( Hatchet::InfoSystem::InfoSystem::instance(), SIGNAL( finished( QString ) ), SLOT( infoSystemFinished( QString ) ) );
}


Scrobbler::~Scrobbler()
{
}


void
Scrobbler::trackStarted( const Hatchet::result_ptr track )
{
    Q_ASSERT( QThread::currentThread() == thread() );

    if ( m_reachedScrobblePoint )
    {
        m_reachedScrobblePoint = false;
        scrobble();
    }

    Hatchet::InfoSystem::InfoStringHash trackInfo;
    trackInfo["title"] = track->track()->track();
    trackInfo["artist"] = track->track()->artist();
    trackInfo["album"] = track->track()->album();
    trackInfo["duration"] = QString::number( track->track()->duration() );
    trackInfo["albumpos"] = QString::number( track->track()->albumpos() );

    QVariantMap playInfo;
    playInfo["trackinfo"] = QVariant::fromValue< Hatchet::InfoSystem::InfoStringHash >( trackInfo );
    playInfo["private"] = HatchetSettings::instance()->privateListeningMode();

    Hatchet::InfoSystem::InfoPushData pushData (
        s_scInfoIdentifier, Hatchet::InfoSystem::InfoSubmitNowPlaying,
        playInfo,
        Hatchet::InfoSystem::PushNoFlag );

    Hatchet::InfoSystem::InfoSystem::instance()->pushInfo( pushData );

    // liblastfm forces 0-length tracks to scrobble after 4 minutes, stupid.
    if ( track->track()->duration() == 0 )
        m_scrobblePoint = lastfm::ScrobblePoint( 30 );
    else
        m_scrobblePoint = lastfm::ScrobblePoint( track->track()->duration() / 2 );
}


void
Scrobbler::trackPaused()
{
    Q_ASSERT( QThread::currentThread() == thread() );
}


void
Scrobbler::trackResumed()
{
    Q_ASSERT( QThread::currentThread() == thread() );
}


void
Scrobbler::trackStopped()
{
    Q_ASSERT( QThread::currentThread() == thread() );

    if ( m_reachedScrobblePoint )
    {
        m_reachedScrobblePoint = false;
        scrobble();
    }
}


void
Scrobbler::engineTick( unsigned int secondsElapsed )
{
    if ( secondsElapsed > m_scrobblePoint )
        m_reachedScrobblePoint = true;
}


void
Scrobbler::scrobble()
{
    Q_ASSERT( QThread::currentThread() == thread() );

    Hatchet::InfoSystem::InfoPushData pushData (
        s_scInfoIdentifier, Hatchet::InfoSystem::InfoSubmitScrobble,
        QVariant(), Hatchet::InfoSystem::PushNoFlag );

    Hatchet::InfoSystem::InfoSystem::instance()->pushInfo( pushData );
}


void
Scrobbler::infoSystemInfo( Hatchet::InfoSystem::InfoRequestData requestData, QVariant output )
{
    Q_UNUSED( output );
    if ( requestData.caller == s_scInfoIdentifier )
        qDebug() << Q_FUNC_INFO;
}


void
Scrobbler::infoSystemFinished( QString target )
{
    if ( target == s_scInfoIdentifier )
    {
        qDebug() << Q_FUNC_INFO;
        qDebug() << "Scrobbler received done signal from InfoSystem";
    }
}
