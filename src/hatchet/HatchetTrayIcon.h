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

#ifndef HATCHET_TRAYICON_H
#define HATCHET_TRAYICON_H

#include <QSystemTrayIcon>
#include <QTimer>
#include <QMenu>

#include "Result.h"

class HatchetTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    HatchetTrayIcon( QObject* parent );
    virtual bool event( QEvent* e );

    void setShowHideWindow( bool show = true );

public slots:
    void setResult( const Hatchet::result_ptr result );

private slots:
    void onAnimationTimer();
    void onActivated( QSystemTrayIcon::ActivationReason reason );
    void showWindow();

    void onPause();
    void onPlay();
    void onStop();
    void onResume();

    void onSocialActionsLoaded();
    void onStopContinueAfterTrackChanged();
    void stopContinueAfterTrackActionTriggered();
    void loveTrackTriggered();

    void menuAboutToShow();

private:
    void refreshToolTip();
    ~HatchetTrayIcon();

    QTimer m_animationTimer;
    Hatchet::result_ptr m_currentTrack;

    QList<QPixmap> m_animationPixmaps;
    int m_currentAnimationFrame;

    QMenu* m_contextMenu;

    QAction* m_showWindowAction;
    QAction* m_stopContinueAfterTrackAction;
    QAction* m_loveTrackAction;
};

#endif // HATCHET_TRAYICON_H

