/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Teo Mrnjavac <teo@kde.org>
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

#ifndef ALBUMSREQUEST_H
#define ALBUMSREQUEST_H

#include "Typedefs.h"
#include "DllMacro.h"

#include <QList>

namespace Hatchet
{

class DLLEXPORT AlbumsRequest
{
public:
    virtual ~AlbumsRequest();

    virtual void enqueue() = 0;

    virtual void setFilter( const QString& filter ) = 0;

protected: //signals
    virtual void albums( const QList< Hatchet::album_ptr >& ) = 0;
};

} //ns

#endif // ALBUMSREQUEST_H
