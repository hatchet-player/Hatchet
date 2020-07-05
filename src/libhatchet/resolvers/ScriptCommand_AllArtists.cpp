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

#include "ScriptCommand_AllArtists.h"

#include "Artist.h"
#include "ScriptAccount.h"
#include "ScriptCollection.h"
#include "ScriptObject.h"
#include "ScriptJob.h"

#include "utils/Logger.h"
#include "../Typedefs.h"

using namespace Hatchet;

ScriptCommand_AllArtists::ScriptCommand_AllArtists( const Hatchet::collection_ptr& collection,
                                                    QObject* parent )
    : ScriptCommand( parent )
    , m_collection( collection )
{
}


void
ScriptCommand_AllArtists::enqueue()
{
    Hatchet::ScriptCollection* collection = qobject_cast< Hatchet::ScriptCollection* >( m_collection.data() );
    if ( collection == 0 )
    {
        reportFailure();
        return;
    }

    exec();
}


void
ScriptCommand_AllArtists::setFilter( const QString& filter )
{
    m_filter = filter;
}


void
ScriptCommand_AllArtists::exec()
{
    Hatchet::ScriptCollection* collection = qobject_cast< Hatchet::ScriptCollection* >( m_collection.data() );
    Q_ASSERT( collection );

    QVariantMap arguments;
    if ( !m_filter.isEmpty() )
    {
        arguments[ "filter" ] = m_filter;
    }

    ScriptJob* job = collection->scriptObject()->invoke( "artists", arguments );
    connect( job, SIGNAL( done( QVariantMap ) ), SLOT( onArtistsJobDone( QVariantMap ) ), Qt::QueuedConnection );
    job->start();
}


void
ScriptCommand_AllArtists::reportFailure()
{
    tDebug() << Q_FUNC_INFO << "for collection" << m_collection->name();
    emit artists( QList< Hatchet::artist_ptr >() );
    emit done();
}


void
ScriptCommand_AllArtists::onArtistsJobDone( const QVariantMap& result )
{
    ScriptJob* job = qobject_cast< ScriptJob* >( sender() );
    Q_ASSERT( job );

    if ( job->error() )
    {
        reportFailure();
        return;
    }

    QList< Hatchet::artist_ptr > a = parseArtistVariantList( result[ "artists" ].toList() );
    emit artists( a );
    emit done();

    job->deleteLater();
}


QList< Hatchet::artist_ptr >
ScriptCommand_AllArtists::parseArtistVariantList( const QVariantList& reslist )
{
    QList< Hatchet::artist_ptr > results;

    foreach( const QVariant& rv, reslist )
    {
        const QString val = rv.toString();
        if ( val.trimmed().isEmpty() )
            continue;

        Hatchet::artist_ptr ap = Hatchet::Artist::get( val, false );

        results << ap;
    }

    return results;
}
