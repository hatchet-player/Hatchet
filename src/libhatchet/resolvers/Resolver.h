/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef RESOLVER_H
#define RESOLVER_H

#include "Typedefs.h"
#include "DllMacro.h"
#include "../DownloadJob.h"

#include <QObject>

// implement this if you can resolve queries to content

/*
    Weight: 1-100, 100 being the best
    Timeout: some millisecond value, after which we try the next highest
             weighted resolver

*/

namespace Hatchet
{
class ScriptJob;

class DLLEXPORT Resolver : public QObject
{
Q_OBJECT

public:
    Resolver( QObject* parent = nullptr );

    virtual QString name() const = 0;
    virtual QPixmap icon( const QSize& size ) const;

    virtual unsigned int weight() const = 0;
    virtual unsigned int timeout() const = 0;

    virtual void resolve( const Hatchet::query_ptr& query ) = 0;
    virtual ScriptJob* getStreamUrl( const result_ptr& result );
    virtual ScriptJob* getDownloadUrl( const result_ptr& result, const DownloadFormat& format );
};

} //ns

#endif // RESOLVER_H
