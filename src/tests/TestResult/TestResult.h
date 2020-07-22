/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef HATCHET_TESTRESULT_H
#define HATCHET_TESTRESULT_H

#include <QtCore>
#include <QtTest>

#include "libhatchet/Result.h"
#include "libhatchet/Track.h"
#include "libhatchet/Source.h"

class TestResult : public QObject
{
    Q_OBJECT

private slots:
    void testGet()
    {
        Hatchet::result_ptr r;

        r = Hatchet::Result::get( "", Hatchet::track_ptr() );
        QVERIFY( !r );

        r = Hatchet::Result::get( "/tmp/test.mp3", Hatchet::track_ptr() );
        QVERIFY( !r);

        Hatchet::track_ptr t = Hatchet::Track::get( "Artist", "Track" );

        r = Hatchet::Result::get( "", t );
        QVERIFY( !r);

        r = Hatchet::Result::get( "/tmp/test.mp3", t );
        QVERIFY( r );
    }
};

#endif
