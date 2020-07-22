/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2013,      Teo Mrnjavac <teo@kde.org>
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

#ifndef DATABASECOMMAND_ALLARTISTS_H
#define DATABASECOMMAND_ALLARTISTS_H

#include <QObject>
#include <QVariantMap>

#include "Artist.h"
#include "collection/ArtistsRequest.h"
#include "collection/Collection.h"
#include "Typedefs.h"
#include "database/DatabaseCommand.h"
#include "Database.h"
#include "DatabaseCollection.h"

#include "DllMacro.h"

namespace Hatchet
{

class DLLEXPORT DatabaseCommand_AllArtists : public DatabaseCommand, public Hatchet::ArtistsRequest
{
Q_OBJECT
public:
    enum SortOrder
    {
        None = 0,
        ModificationTime = 1
    };

    explicit DatabaseCommand_AllArtists( const Hatchet::collection_ptr& collection = Hatchet::collection_ptr(), QObject* parent = 0 );
    virtual ~DatabaseCommand_AllArtists();

    void exec( DatabaseImpl* ) Q_DECL_OVERRIDE;

    bool doesMutates() const Q_DECL_OVERRIDE { return false; }
    QString commandname() const Q_DECL_OVERRIDE { return "allartists"; }

    void enqueue() Q_DECL_OVERRIDE { Database::instance()->enqueue( Hatchet::dbcmd_ptr( this ) ); }

    void setLimit( unsigned int amount ) { m_amount = amount; }
    void setSortOrder( DatabaseCommand_AllArtists::SortOrder order ) { m_sortOrder = order; }
    void setSortDescending( bool descending ) { m_sortDescending = descending; }
    void setFilter( const QString& filter ) override { m_filter = filter; }

signals:
    void artists( const QList<Hatchet::artist_ptr>& ) override;
    void done();

private:
    QSharedPointer< DatabaseCollection > m_collection;
    unsigned int m_amount;
    DatabaseCommand_AllArtists::SortOrder m_sortOrder;
    bool m_sortDescending;
    QString m_filter;
};

}

#endif // DATABASECOMMAND_ALLARTISTS_H