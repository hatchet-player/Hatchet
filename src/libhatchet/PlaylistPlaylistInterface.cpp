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

#include "PlaylistPlaylistInterface.h"

#include "utils/Logger.h"

#include "Playlist.h"
#include "PlaylistEntry.h"
#include "SourceList.h"

using namespace Hatchet;


PlaylistPlaylistInterface::PlaylistPlaylistInterface( Hatchet::Playlist* playlist )
    : Hatchet::PlaylistInterface()
    , m_playlist( playlist )
{
}


PlaylistPlaylistInterface::~PlaylistPlaylistInterface()
{
    m_playlist = 0;
}


int
PlaylistPlaylistInterface::trackCount() const
{
    return ( m_playlist.isNull() ? 0 : m_playlist.data()->entries().count() );
}


QList< Hatchet::query_ptr >
PlaylistPlaylistInterface::tracks() const
{
    QList<Hatchet::query_ptr> queries;
    foreach( const plentry_ptr& p, ( m_playlist.isNull() ? QList< Hatchet::plentry_ptr >() : m_playlist.data()->entries() ) )
        queries << p->query();

    return queries;
}
