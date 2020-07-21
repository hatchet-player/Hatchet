/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2011,      Leo Franchi <lfranchi@kde.org>
 *   Copyright 2011,      Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2011-2016, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2013,      Uwe L. Korn <uwelk@xhochy.com>
 *   Copyright 2013,      Teo Mrnjavac <teo@kde.org>
 *   Copyright 2014,      Dominik Schmidt <domme@tomahawk-player.org>
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

#include "HatchetLinkGeneratorPlugin.h"

#include "../playlist/dynamic/GeneratorInterface.h"
#include "../playlist/dynamic/DynamicPlaylist.h"
#include "../Track.h"
#include "../Artist.h"
#include "../Album.h"
#include "../resolvers/SyncScriptJob.h"
#include "../utils/Logger.h"

QString
Hatchet::Utils::HatchetLinkGeneratorPlugin::hostname() const
{
    return QString( "http://toma.hk" );

}


Hatchet::ScriptJob*
Hatchet::Utils::HatchetLinkGeneratorPlugin::openLink( const QString& title, const QString& artist, const QString& album ) const
{
    QUrl link( QString( "%1/open/track/" ).arg( hostname() ) );

    if ( !artist.isEmpty() )
       HatchetUtils::urlAddQueryItem( link, "artist", artist );
    if ( !title.isEmpty() )
        HatchetUtils::urlAddQueryItem( link, "title", title );
    if ( !album.isEmpty() )
        HatchetUtils::urlAddQueryItem( link, "album", album );

    QVariantMap data;
    data[ "url" ] = link;
    data[ "shortenLink" ] = true;

    return new SyncScriptJob( data );
}


Hatchet::ScriptJob*
Hatchet::Utils::HatchetLinkGeneratorPlugin::openLink( const Hatchet::artist_ptr& artist ) const
{
    QVariantMap data;
    data[ "url" ] = QString( "%1/artist/%2" ).arg( hostname() ).arg( artist->name() );
    return new SyncScriptJob( data );
}


Hatchet::ScriptJob*
Hatchet::Utils::HatchetLinkGeneratorPlugin::openLink( const Hatchet::album_ptr& album ) const
{
    QVariantMap data;
    data[ "url" ] = QUrl::fromUserInput( QString( "%1/album/%2/%3" ).arg( hostname() ).arg( album->artist().isNull() ? QString() : album->artist()->name() ).arg( album->name() ) );;
    return new SyncScriptJob( data );
}

