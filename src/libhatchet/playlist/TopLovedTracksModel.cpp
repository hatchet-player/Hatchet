/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2012, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2013,      Uwe L. Korn <uwelk@xhochy.com>
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

#include "TopLovedTracksModel_p.h"

#include "database/Database.h"
#include "database/commands/GenericSelect.h"
#include "Source.h"

using namespace Hatchet;


TopLovedTracksModel::TopLovedTracksModel( QObject* parent )
    : LovedTracksModel( parent )
{
}


TopLovedTracksModel::~TopLovedTracksModel()
{
}


void
TopLovedTracksModel::loadTracks()
{
    Q_D( TopLovedTracksModel );
    startLoading();

    QString sql;
    if ( d->source.isNull() )
    {
        sql = QString( "SELECT track.name, artist.name, source, COUNT(*) as counter "
                       "FROM social_attributes, track, artist "
                       "WHERE social_attributes.id = track.id AND artist.id = track.artist AND social_attributes.k = 'Love' AND social_attributes.v = 'true' "
                       "GROUP BY track.id "
                       "ORDER BY counter DESC, social_attributes.timestamp DESC LIMIT %1" )
                .arg( d->limit );
    }
    else
    {
        sql = QString( "SELECT track.name, artist.name, COUNT(*) as counter "
                       "FROM social_attributes, track, artist "
                       "WHERE social_attributes.id = track.id AND artist.id = track.artist AND social_attributes.k = 'Love' AND social_attributes.v = 'true' AND social_attributes.source %1 "
                       "GROUP BY track.id "
                       "ORDER BY counter DESC, social_attributes.timestamp DESC "
                       )
                .arg( d->source->isLocal() ? "IS NULL" : QString( "= %1" ).arg( d->source->id() ) );
    }

    DatabaseCommand_GenericSelect* cmd = new DatabaseCommand_GenericSelect( sql, DatabaseCommand_GenericSelect::Track, -1, 0 );
    connect( cmd, SIGNAL( tracks( QList<Hatchet::query_ptr> ) ), this, SLOT( tracksLoaded( QList<Hatchet::query_ptr> ) ) );
    Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );
}
