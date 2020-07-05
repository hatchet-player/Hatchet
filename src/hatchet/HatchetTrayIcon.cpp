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

#include "HatchetTrayIcon.h"

#include "audio/AudioEngine.h"
#include "collection/Collection.h"
#include "utils/Logger.h"
#include "utils/HatchetUtilsGui.h"

#include "ActionCollection.h"
#include "Artist.h"
#include "Query.h"
#include "Source.h"
#include "HatchetApp.h"
#include "HatchetWindow.h"
#include "Track.h"

#include <QWheelEvent>

HatchetTrayIcon::HatchetTrayIcon( QObject* parent )
    : QSystemTrayIcon( parent )
    , m_currentAnimationFrame( 0 )
    , m_showWindowAction( 0 )
    , m_stopContinueAfterTrackAction( 0 )
    , m_loveTrackAction( 0 )
{
#ifdef Q_OS_MAC
    QIcon icon( RESPATH "icons/hatchet-grayscale-icon-128x128.png" );
#else
    QIcon icon( RESPATH "icons/hatchet-icon-128x128.png" );
#endif

    setIcon( icon );

    refreshToolTip();

    m_contextMenu = new QMenu();
    m_contextMenu->setFont( HatchetUtils::systemFont() );
    setContextMenu( m_contextMenu );

    m_loveTrackAction = new QAction( this );
    m_stopContinueAfterTrackAction = new QAction( this );

    ActionCollection *ac = ActionCollection::instance();
    m_contextMenu->addAction( ac->getAction( "playPause" ) );
    m_contextMenu->addAction( ac->getAction( "stop" ) );
    m_contextMenu->addSeparator();
    m_contextMenu->addAction( m_loveTrackAction );
    m_contextMenu->addAction( m_stopContinueAfterTrackAction );
    m_contextMenu->addSeparator();
    m_contextMenu->addAction( ac->getAction( "previousTrack" ) );
    m_contextMenu->addAction( ac->getAction( "nextTrack" ) );
    /*
    m_contextMenu->addSeparator();
    m_contextMenu->addAction( ActionCollection::instance()->getAction( "togglePrivacy" ) );
    */

#ifdef Q_OS_MAC
    // On mac you can close the windows while leaving the app open. We then need a way to show the main window again
    m_contextMenu->addSeparator();
    m_showWindowAction = m_contextMenu->addAction( tr( "Hide %applicationName Window" ) );
    m_showWindowAction->setData( true );
    connect( m_showWindowAction, SIGNAL( triggered() ), this, SLOT( showWindow() ) );

    connect( m_contextMenu, SIGNAL( aboutToShow() ), this, SLOT( menuAboutToShow() ) );
#endif

    m_contextMenu->addSeparator();
    m_contextMenu->addAction( ac->getAction( "quit" ) );

    connect( m_loveTrackAction, SIGNAL( triggered() ), SLOT( loveTrackTriggered() ) );
    connect( m_stopContinueAfterTrackAction, SIGNAL( triggered() ), SLOT( stopContinueAfterTrackActionTriggered() ) );

    connect( AudioEngine::instance(), SIGNAL( loading( Hatchet::result_ptr ) ), SLOT( setResult( Hatchet::result_ptr ) ) );
    connect( AudioEngine::instance(), SIGNAL( started( Hatchet::result_ptr ) ), SLOT( onPlay() ) );
    connect( AudioEngine::instance(), SIGNAL( resumed() ), SLOT( onResume() ) );
    connect( AudioEngine::instance(), SIGNAL( stopped() ), SLOT( onStop() ) );
    connect( AudioEngine::instance(), SIGNAL( paused() ),  SLOT( onPause() ) );
    connect( AudioEngine::instance(), SIGNAL( stopAfterTrackChanged() ), SLOT( onStopContinueAfterTrackChanged() ) );

    connect( &m_animationTimer, SIGNAL( timeout() ), SLOT( onAnimationTimer() ) );
    connect( this, SIGNAL( activated( QSystemTrayIcon::ActivationReason ) ), SLOT( onActivated( QSystemTrayIcon::ActivationReason ) ) );

    onStop();
    show();
}


HatchetTrayIcon::~HatchetTrayIcon()
{
    delete m_contextMenu;
}


void
HatchetTrayIcon::setShowHideWindow( bool show )
{
    if ( show )
    {
        m_showWindowAction->setText( tr( "Hide %applicationName Window" ) );
        m_showWindowAction->setData( show );
    }
    else
    {
        m_showWindowAction->setText( tr( "Show %applicationName Window" ) );
    }

    m_showWindowAction->setData( show );
}


void
HatchetTrayIcon::showWindow()
{
    if( !m_showWindowAction->data().toBool() )
    {
        APP->mainWindow()->show();
        APP->mainWindow()->raise();

        setShowHideWindow( true );
    }
    else
    {
        APP->mainWindow()->hide();

        setShowHideWindow( false );
    }
}


void
HatchetTrayIcon::menuAboutToShow()
{
    // When using Cmd-H on mac to hide a window, it is an OS-level hide that is different from QWidget::hide().
    // Qt returns isVisible() == true for windows that are hidden with Cmd-H, which is weird. isActiveWindow() returns
    // the proper information though.
    setShowHideWindow( APP->mainWindow()->isActiveWindow() );
}


void
HatchetTrayIcon::setResult( const Hatchet::result_ptr result )
{
    if ( m_currentTrack )
    {
        disconnect( m_currentTrack->track().data(), SIGNAL( socialActionsLoaded() ), this, SLOT( onSocialActionsLoaded() ) );
    }

    m_currentTrack = result;
    refreshToolTip();

    if ( result )
        connect( result->track().data(), SIGNAL( socialActionsLoaded() ), SLOT( onSocialActionsLoaded() ), Qt::UniqueConnection );

    onSocialActionsLoaded();
    onStopContinueAfterTrackChanged();
}


void
HatchetTrayIcon::onStopContinueAfterTrackChanged()
{
    if ( m_currentTrack && AudioEngine::instance()->stopAfterTrack() && m_currentTrack->track()->equals( AudioEngine::instance()->stopAfterTrack()->track() ) )
        m_stopContinueAfterTrackAction->setText( tr( "&Continue Playback after current Track" ) );
    else
        m_stopContinueAfterTrackAction->setText( tr( "&Stop Playback after current Track" ) );
}


void
HatchetTrayIcon::refreshToolTip()
{
    #ifdef Q_OS_MAC
    // causes issues with OS X menubar, also none
    // of the other OS X menubar icons have a tooltip
    return;
    #endif

    QString tip;
    if ( !m_currentTrack.isNull() )
    {
        tip = m_currentTrack->track()->artist() + " " + QChar( 8211 ) /*en dash*/ + " " + m_currentTrack->track()->track();
    }
    else
    {
        tip = tr( "Currently not playing." );
    }

    #ifdef Q_OS_WIN
        // Good old crappy Win32
        tip.replace( "&", "&&&" );
    #endif

    setToolTip( tip );
}


void
HatchetTrayIcon::onAnimationTimer()
{
/*    m_currentAnimationFrame++;
    if( m_currentAnimationFrame >= m_animationPixmaps.count() )
        m_currentAnimationFrame = 0;

    setIcon( m_animationPixmaps.at( m_currentAnimationFrame ) );*/
}


void
HatchetTrayIcon::onActivated( QSystemTrayIcon::ActivationReason reason )
{
#ifdef Q_OS_MAC
    return;
#endif

    switch( reason )
    {
        case QSystemTrayIcon::Trigger:
        {
            HatchetWindow* mainwindow = APP->mainWindow();
            if (mainwindow->isActiveWindow())
            {
                mainwindow->hide();
            }
            else
            {
                HatchetUtils::bringToFront();
            }
        }
        break;

        case QSystemTrayIcon::MiddleClick:
        {
            AudioEngine::instance()->playPause();
        }
        break;

        default:
            break;
    }
}


void
HatchetTrayIcon::onPause()
{
    ActionCollection::instance()->getAction( "playPause" )->setText( tr( "Play" ) );
}


void
HatchetTrayIcon::onPlay()
{
    m_loveTrackAction->setEnabled( true );
    m_stopContinueAfterTrackAction->setEnabled( true );

    onResume();
}


void
HatchetTrayIcon::onStop()
{
    m_loveTrackAction->setEnabled( false );
    m_stopContinueAfterTrackAction->setEnabled( false );

    setResult( Hatchet::result_ptr() );
    onPause();
}


void
HatchetTrayIcon::onResume()
{
    ActionCollection::instance()->getAction( "playPause" )->setText( tr( "Pause" ) );
}


void
HatchetTrayIcon::loveTrackTriggered()
{
    if ( !m_currentTrack )
        return;

    m_currentTrack->track()->setLoved( !m_currentTrack->track()->loved() );
}


void
HatchetTrayIcon::stopContinueAfterTrackActionTriggered()
{
    if ( !m_currentTrack )
        return;

    if ( !AudioEngine::instance()->stopAfterTrack() || !m_currentTrack->track()->equals( AudioEngine::instance()->stopAfterTrack()->track() ) )
        AudioEngine::instance()->setStopAfterTrack( m_currentTrack->toQuery() );
    else
        AudioEngine::instance()->setStopAfterTrack( Hatchet::query_ptr() );
}


void
HatchetTrayIcon::onSocialActionsLoaded()
{
    m_loveTrackAction->setText( tr( "&Love" ) );
    m_loveTrackAction->setIcon( QIcon( RESPATH "images/loved.svg" ) );

    if ( !m_currentTrack )
        return;

    if ( m_currentTrack->track()->loved() )
    {
        m_loveTrackAction->setText( tr( "Un-&Love" ) );
        m_loveTrackAction->setIcon( QIcon( RESPATH "images/not-loved.svg" ) );
    }
}


bool
HatchetTrayIcon::event( QEvent* e )
{
    // Beginning with Qt 4.3, QSystemTrayIcon supports wheel events, but only
    // on X11. Let's make it adjust the volume.
    if ( e->type() == QEvent::Wheel )
    {
        if ( ((QWheelEvent*)e)->delta() > 0 )
        {
            AudioEngine::instance()->raiseVolume();
        }
        else
        {
            AudioEngine::instance()->lowerVolume();
        }

        return true;
    }

    return QSystemTrayIcon::event( e );
}
