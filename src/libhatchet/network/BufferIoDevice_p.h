/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2013, Uwe L. Korn <uwelk@xhochy.com>
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

#ifndef BUFFERIODEVICE_P_H
#define BUFFERIODEVICE_P_H

#include "BufferIoDevice.h"

#include <QMutex>

class BufferIODevicePrivate
{
public:
    BufferIODevicePrivate( BufferIODevice* q, unsigned int size = 0 )
        : q_ptr ( q )
        , size( size )
        , received( 0 )
        , pos( 0 )

    {
    }
    BufferIODevice* q_ptr;
    Q_DECLARE_PUBLIC ( BufferIODevice )

private:
    QList<QByteArray> buffer;
    mutable QMutex mut;
    unsigned int size;
    unsigned int received;
    unsigned int pos;
};

#endif // BUFFERIODEVICE_P_H
