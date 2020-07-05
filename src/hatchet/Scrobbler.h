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

#ifndef HATCHET_SCROBBLER_H
#define HATCHET_SCROBBLER_H

#include "Result.h"
#include "infosystem/InfoSystem.h"

#include <lastfm5/ScrobblePoint.h>
#include <QObject>

/**
 * Simple class that listens to signals from AudioEngine and scrobbles
 *  what it is playing.
 */
class Scrobbler : public QObject
{
    Q_OBJECT
public:
    Scrobbler( QObject* parent = 0 );
    virtual ~Scrobbler();

public slots:
    void trackStarted( const Hatchet::result_ptr );
    void trackPaused();
    void trackResumed();
    void trackStopped();
    void engineTick( unsigned int secondsElapsed );

    void infoSystemInfo( Hatchet::InfoSystem::InfoRequestData requestData, QVariant output );
    void infoSystemFinished( QString target );

private:
    void scrobble();

    bool m_reachedScrobblePoint;
    lastfm::ScrobblePoint m_scrobblePoint;
};


#endif
