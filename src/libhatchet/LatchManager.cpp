/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
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

#include "LatchManager.h"

#include "ActionCollection.h"
#include "audio/AudioEngine.h"
#include "database/Database.h"

#include "SourceList.h"
#include "database/commands/SocialAction.h"
#include "SourcePlaylistInterface.h"

#include <QAction>


using namespace Hatchet;

LatchManager::LatchManager( QObject* parent )
    : QObject( parent )
    , m_state( NotLatched )
{
    connect( AudioEngine::instance(), SIGNAL( playlistChanged( Hatchet::playlistinterface_ptr ) ), this, SLOT( playlistChanged( Hatchet::playlistinterface_ptr ) ) );
    connect( AudioEngine::instance(), SIGNAL( paused() ), SLOT( audioPaused() ) );
}

LatchManager::~LatchManager()
{

}


bool
LatchManager::isLatched( const source_ptr& src )
{
    return m_state == Latched && m_latchedOnTo == src;
}


void
LatchManager::latchRequest( const source_ptr& source )
{
    qDebug() << Q_FUNC_INFO;
    if ( isLatched( source ) )
        return;

    m_state = Latching;
    m_waitingForLatch = source;
    AudioEngine::instance()->playItem( source->playlistInterface(), source->playlistInterface()->nextResult() );
}


void
LatchManager::playlistChanged( Hatchet::playlistinterface_ptr )
{
    // If we were latched on and changed, send the listening along stop
    if ( m_latchedOnTo.isNull() )
    {
        if ( m_waitingForLatch.isNull() )
            return; // Neither latched on nor waiting to be latched on, no-op

        m_latchedOnTo = m_waitingForLatch;
        m_latchedInterface = m_waitingForLatch->playlistInterface();
        m_waitingForLatch.clear();
        m_state = Latched;

        DatabaseCommand_SocialAction* cmd = new DatabaseCommand_SocialAction();
        cmd->setSource( SourceList::instance()->getLocal() );
        cmd->setAction( "latchOn");
        cmd->setComment( m_latchedOnTo->nodeId() );
        cmd->setTimestamp( QDateTime::currentDateTime().toTime_t() );
        Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );

        QAction *latchOnAction = ActionCollection::instance()->getAction( "latchOn" );
        latchOnAction->setText( tr( "&Catch Up" ) );
        latchOnAction->setIcon( QIcon() );

        // If not, then keep waiting
        return;
    }

    // We're current latched, and the user changed playlist, so stop
    SourcePlaylistInterface* origsourcepi = dynamic_cast< SourcePlaylistInterface* >( m_latchedInterface.data() );
    Q_ASSERT( origsourcepi );
    const source_ptr source = SourceList::instance()->get( origsourcepi->source()->id() );

    DatabaseCommand_SocialAction* cmd = new DatabaseCommand_SocialAction();
    cmd->setSource( SourceList::instance()->getLocal() );
    cmd->setAction( "latchOff");
    cmd->setComment( source->nodeId() );
    cmd->setTimestamp( QDateTime::currentDateTime().toTime_t() );
    Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );

    if ( !m_waitingForLatch.isNull() &&
          m_waitingForLatch != m_latchedOnTo )
    {
        // We are asked to latch on immediately to another source
        m_latchedOnTo.clear();
        m_latchedInterface.clear();

        // call ourselves to hit the "create latch" condition
        playlistChanged( Hatchet::playlistinterface_ptr() );
        return;
    }
    m_latchedOnTo.clear();
    m_waitingForLatch.clear();
    m_latchedInterface.clear();

    m_state = NotLatched;

    QAction *latchOnAction = ActionCollection::instance()->getAction( "latchOn" );
    latchOnAction->setText( tr( "&Listen Along" ) );
    latchOnAction->setIcon( QIcon( RESPATH "images/headphones-sidebar.png" ) );
}


void
LatchManager::audioPaused()
{
    if ( !m_latchedOnTo.isNull() )
    {
        SourcePlaylistInterface* plInterface = qobject_cast< SourcePlaylistInterface* >( m_latchedOnTo->playlistInterface().data() );
        Q_ASSERT( plInterface );
        plInterface->audioPaused();
    }
}


void
LatchManager::catchUpRequest()
{
    //it's a catch-up -- logic in audioengine should take care of it
    AudioEngine::instance()->next();
}


void
LatchManager::unlatchRequest( const source_ptr& source )
{
    Q_UNUSED( source );
    AudioEngine::instance()->stop();
    AudioEngine::instance()->setPlaylist( Hatchet::playlistinterface_ptr() );

    QAction *latchOnAction = ActionCollection::instance()->getAction( "latchOn" );
    latchOnAction->setText( tr( "&Listen Along" ) );
    latchOnAction->setIcon( QIcon( RESPATH "images/headphones-sidebar.png" ) );
}


void
LatchManager::latchModeChangeRequest( const Hatchet::source_ptr& source, bool realtime )
{
    if ( !isLatched( source ) )
        return;

    source->playlistInterface()->setLatchMode( realtime ? Hatchet::PlaylistModes::RealTime : Hatchet::PlaylistModes::StayOnSong );
    if ( realtime )
        catchUpRequest();
}
