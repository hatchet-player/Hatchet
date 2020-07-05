/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
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

#include "SourcePlaylistInterface.h"

#include "audio/AudioEngine.h"
#include "utils/Logger.h"

#include "Pipeline.h"
#include "Result.h"
#include "Source.h"

using namespace Hatchet;


SourcePlaylistInterface::SourcePlaylistInterface( Hatchet::Source* source, Hatchet::PlaylistModes::LatchMode latchMode )
    : PlaylistInterface()
    , m_source( source )
    , m_currentItem( 0 )
    , m_gotNextItem( false )
{
    setLatchMode( latchMode );

    if ( !m_source.isNull() )
        connect( m_source.data(), SIGNAL( playbackStarted( const Hatchet::track_ptr& ) ), SLOT( onSourcePlaybackStarted( const Hatchet::track_ptr& ) ) );
}


SourcePlaylistInterface::~SourcePlaylistInterface()
{
    m_source = 0;
}


void
SourcePlaylistInterface::setCurrentIndex( qint64 index )
{
    if ( index == 1 )
        m_gotNextItem = false;
}


qint64
SourcePlaylistInterface::indexOfResult( const Hatchet::result_ptr& result ) const
{
    if ( nextResult() == result )
        return 1;
    else
        return -1;
}


qint64
SourcePlaylistInterface::siblingIndex( int itemsAway, qint64 rootIndex ) const
{
    Q_UNUSED( itemsAway );
    Q_UNUSED( rootIndex );

    if ( nextResult() )
        return 1;
    else
        return -1;
}


Hatchet::result_ptr
SourcePlaylistInterface::nextResult() const
{
    if ( !sourceValid() )
    {
        tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "Source no longer valid";
        m_currentItem = Hatchet::result_ptr();
        return m_currentItem;
    }
    else if ( !hasNextResult() )
    {
        tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "This song was already fetched or the source isn't playing anything";
        return Hatchet::result_ptr();
    }

    if ( m_source.data()->currentTrack()->numResults() )
    {
        m_currentItem = m_source.data()->currentTrack()->results().first();
    }
    else
        m_currentItem = result_ptr();

    return m_currentItem;
}


result_ptr
SourcePlaylistInterface::currentItem() const
{
    return m_currentItem;
}


bool
SourcePlaylistInterface::sourceValid() const
{
    tDebug( LOGEXTRA ) << Q_FUNC_INFO;
    if ( m_source.isNull() || m_source.data()->currentTrack().isNull() )
        return false;

    return true;
}


bool
SourcePlaylistInterface::hasNextResult() const
{
    if ( !sourceValid() )
        return false;

    return m_gotNextItem;
}


QList<Hatchet::query_ptr>
SourcePlaylistInterface::tracks() const
{
    QList<Hatchet::query_ptr> tracks;
    if ( nextResult() )
        tracks << nextResult()->toQuery();

    return tracks;
}


QPointer< Hatchet::Source >
SourcePlaylistInterface::source() const
{
    return m_source;
}


void
SourcePlaylistInterface::reset()
{
    if ( m_currentItem.isNull() )
        m_gotNextItem = false;
    else
        m_gotNextItem = true;
}


void
SourcePlaylistInterface::onSourcePlaybackStarted( const Hatchet::track_ptr& track )
{
    tDebug( LOGVERBOSE ) << Q_FUNC_INFO;

    query_ptr query = track->toQuery();
    connect( query.data(), SIGNAL( resolvingFinished( bool ) ), SLOT( resolvingFinished( bool ) ) );
    Pipeline::instance()->resolve( query );
    m_gotNextItem = false;
}


void
SourcePlaylistInterface::resolvingFinished( bool hasResults )
{
    tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "Has results?" << ( hasResults ? "true" : "false" );
    if ( hasResults )
    {
        m_gotNextItem = true;
    }

    emit nextTrackAvailable( hasResults );
}


Hatchet::query_ptr
SourcePlaylistInterface::queryAt( qint64 index ) const
{
    if ( index == 1 )
    {
        Hatchet::result_ptr res = nextResult();
        return res->toQuery();
    }
    else
        return Hatchet::query_ptr();
}


Hatchet::result_ptr
SourcePlaylistInterface::resultAt( qint64 index ) const
{
    if ( index == 1 )
        return nextResult();
    else
        return Hatchet::result_ptr();
}
