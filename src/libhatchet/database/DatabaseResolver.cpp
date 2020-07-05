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

#include "DatabaseResolver.h"

#include "database/Database.h"
#include "database/DatabaseCommand_Resolve.h"
#include "network/Servent.h"
#include "utils/Logger.h"

#include "Pipeline.h"
#include "PlaylistEntry.h"
#include "Source.h"


DatabaseResolver::DatabaseResolver( int weight )
    : Resolver()
    , m_weight( weight )
{
}


void
DatabaseResolver::resolve( const Hatchet::query_ptr& query )
{
    Hatchet::DatabaseCommand_Resolve* cmd = new Hatchet::DatabaseCommand_Resolve( query );

    connect( cmd, SIGNAL( results( Hatchet::QID, QList< Hatchet::result_ptr > ) ),
                    SLOT( gotResults( Hatchet::QID, QList< Hatchet::result_ptr > ) ), Qt::QueuedConnection );
    connect( cmd, SIGNAL( albums( Hatchet::QID, QList< Hatchet::album_ptr > ) ),
                    SLOT( gotAlbums( Hatchet::QID, QList< Hatchet::album_ptr > ) ), Qt::QueuedConnection );
    connect( cmd, SIGNAL( artists( Hatchet::QID, QList< Hatchet::artist_ptr > ) ),
                    SLOT( gotArtists( Hatchet::QID, QList< Hatchet::artist_ptr > ) ), Qt::QueuedConnection );

    Hatchet::Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );
}


void
DatabaseResolver::gotResults( const Hatchet::QID qid, QList< Hatchet::result_ptr> results )
{
    tDebug( LOGVERBOSE ) << Q_FUNC_INFO << qid << results.length();

    foreach ( const Hatchet::result_ptr& r, results )
        r->setResolvedByResolver( this );

    Hatchet::Pipeline::instance()->reportResults( qid, this, results );
}


void
DatabaseResolver::gotAlbums( const Hatchet::QID qid, QList< Hatchet::album_ptr> albums )
{
    Hatchet::Pipeline::instance()->reportAlbums( qid, albums );
}


void
DatabaseResolver::gotArtists( const Hatchet::QID qid, QList< Hatchet::artist_ptr> artists )
{
    Hatchet::Pipeline::instance()->reportArtists( qid, artists );
}


QString
DatabaseResolver::name() const
{
    return QString( "DatabaseResolver" );
}
