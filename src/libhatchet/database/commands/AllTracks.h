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

#ifndef DATABASECOMMAND_ALLTRACKS_H
#define DATABASECOMMAND_ALLTRACKS_H

#include <QObject>
#include <QVariantMap>

#include "database/DatabaseCommand.h"
#include "Database.h"
#include "DatabaseCollection.h"
#include "collection/Collection.h"
#include "collection/TracksRequest.h"
#include "Typedefs.h"
#include "Query.h"
#include "Artist.h"
#include "Album.h"

#include "DllMacro.h"

namespace Hatchet
{

class DLLEXPORT DatabaseCommand_AllTracks : public DatabaseCommand, public Hatchet::TracksRequest
{
Q_OBJECT
public:
    enum SortOrder {
        None = 0,
        Album = 1,
        ModificationTime = 2,
        AlbumPosition = 3
    };

    explicit DatabaseCommand_AllTracks( const Hatchet::collection_ptr& collection = Hatchet::collection_ptr(), QObject* parent = nullptr )
        : DatabaseCommand( parent )
        , m_collection( collection.objectCast< DatabaseCollection >() )
        , m_artist( nullptr )
        , m_album( nullptr )
        , m_amount( 0 )
        , m_sortOrder( DatabaseCommand_AllTracks::None )
        , m_sortDescending( false )
    {}

    void exec( DatabaseImpl* ) override;

    bool doesMutates() const override { return false; }
    QString commandname() const override { return "alltracks"; }

    void enqueue() override { Database::instance()->enqueue( Hatchet::dbcmd_ptr( this ) ); }

    void setArtist( const Hatchet::artist_ptr& artist ) { m_artist = artist; }
    void setAlbum( const Hatchet::album_ptr& album ) { m_album = album; }

    void setLimit( unsigned int amount ) { m_amount = amount; }
    void setSortOrder( DatabaseCommand_AllTracks::SortOrder order ) { m_sortOrder = order; }
    void setSortDescending( bool descending ) { m_sortDescending = descending; }

signals:
    void tracks( const QList<Hatchet::query_ptr>&, const QVariant& data );
    void tracks( const QList<Hatchet::query_ptr>& ) override;
    void done( const Hatchet::collection_ptr& );

private:
    QSharedPointer< DatabaseCollection > m_collection;

    Hatchet::artist_ptr m_artist;
    Hatchet::album_ptr m_album;

    unsigned int m_amount;
    DatabaseCommand_AllTracks::SortOrder m_sortOrder;
    bool m_sortDescending;
};

}

#endif // DATABASECOMMAND_ALLTRACKS_H
