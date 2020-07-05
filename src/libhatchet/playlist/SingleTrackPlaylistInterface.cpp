/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 * 
 *   Copyright 2012 Leo Franchi <lfranchi@kde.org>
 *   Copyright 2012, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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


#include "SingleTrackPlaylistInterface.h"

namespace Hatchet
{

SingleTrackPlaylistInterface::SingleTrackPlaylistInterface( const Hatchet::query_ptr& query )
    : PlaylistInterface()
    , m_track( query )
{
}


Hatchet::result_ptr
SingleTrackPlaylistInterface::currentItem() const
{
    if ( m_track && m_track->numResults() )
        return m_track->results().first();

    return result_ptr();
}


Hatchet::result_ptr
SingleTrackPlaylistInterface::resultAt( qint64 index ) const
{
    if ( index == 0 && m_track && m_track->numResults() )
        return m_track->results().first();

    return result_ptr();
}


Hatchet::query_ptr
SingleTrackPlaylistInterface::queryAt( qint64 index ) const
{
    if ( index == 0 )
        return m_track;

    return query_ptr();
}


qint64
SingleTrackPlaylistInterface::indexOfResult( const Hatchet::result_ptr& result ) const
{
    if ( m_track && m_track->results().contains( result ) )
        return 0;

    return -1;
}


qint64
SingleTrackPlaylistInterface::indexOfQuery( const Hatchet::query_ptr& query ) const
{
    if ( m_track == query )
        return 0;
    
    return -1;
}


QList< Hatchet::query_ptr >
SingleTrackPlaylistInterface::tracks() const
{
    QList< query_ptr > ql;

    if ( m_track )
        ql << m_track;

    return ql;
}

}

