/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2013,      Teo Mrnjavac <teo@kde.org>
 *   Copyright 2013-2014, Uwe L. Korn <uwelk@xhochy.com>
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

#ifndef HATCHET_URLHANDLER_H
#define HATCHET_URLHANDLER_H

#include "DllMacro.h"
#include "Typedefs.h"

#include <functional>

typedef std::function< void( const Hatchet::result_ptr&, const QString&,
                               std::function< void( const QString&, QSharedPointer< QIODevice >& ) > )> IODeviceFactoryFunc;
typedef std::function< void( const Hatchet::result_ptr&, const QString&,
                               std::function< void( const QString& ) > )> UrlTranslatorFunc;
typedef std::function< void ( const QString&, QSharedPointer< QIODevice >& ) > IODeviceCallback;


namespace Hatchet
{

namespace UrlHandler
{

    DLLEXPORT void getIODeviceForUrl( const Hatchet::result_ptr&, const QString& url,
                                      std::function< void ( const QString, QSharedPointer< QIODevice > ) > callback );
    DLLEXPORT void registerIODeviceFactory( const QString& proto, IODeviceFactoryFunc fac );
    DLLEXPORT void localFileIODeviceFactory( const Hatchet::result_ptr& result, const QString& url,
                                             std::function< void ( const QString&, QSharedPointer< QIODevice >& ) > callback );
    DLLEXPORT void httpIODeviceFactory( const Hatchet::result_ptr& result, const QString& url,
                                       std::function< void ( const QString&, QSharedPointer< QIODevice >& ) > callback );
} // namespace UrlHandler

} // namespace Hatchet

#endif // HATCHET_URLHANDLER_H
