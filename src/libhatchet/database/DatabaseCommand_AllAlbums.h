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

#ifndef DATABASECOMMAND_ALLALBUMS_H
#define DATABASECOMMAND_ALLALBUMS_H

#include <QObject>
#include <QVariantMap>

#include "Album.h"
#include "Artist.h"
#include "collection/Collection.h"
#include "collection/AlbumsRequest.h"
#include "Typedefs.h"
#include "DatabaseCommand.h"
#include "Database.h"
#include "DatabaseCollection.h"

#include "DllMacro.h"

namespace Hatchet
{

class DLLEXPORT DatabaseCommand_AllAlbums : public DatabaseCommand, public Hatchet::AlbumsRequest
{
Q_OBJECT
public:
    enum SortOrder {
        None = 0,
        ModificationTime = 1
    };

    explicit DatabaseCommand_AllAlbums( const Hatchet::collection_ptr& collection = Hatchet::collection_ptr(),
                                        const Hatchet::artist_ptr& artist = Hatchet::artist_ptr(),
                                        QObject* parent = 0 );
    virtual ~DatabaseCommand_AllAlbums();

    virtual void exec( DatabaseImpl* );

    virtual bool doesMutates() const { return false; }
    virtual QString commandname() const { return "allalbums"; }

    virtual void enqueue() { Database::instance()->enqueue( Hatchet::dbcmd_ptr( this ) ); }

    Hatchet::collection_ptr collection() const { return m_collection; }

    void execForCollection( DatabaseImpl* );
    void execForArtist( DatabaseImpl* );

    void setArtist( const Hatchet::artist_ptr& artist );
    void setLimit( unsigned int amount ) { m_amount = amount; }
    void setSortOrder( DatabaseCommand_AllAlbums::SortOrder order ) { m_sortOrder = order; }
    void setSortDescending( bool descending ) { m_sortDescending = descending; }
    void setFilter( const QString& filter ) { m_filter = filter; }

signals:
    void albums( const QList<Hatchet::album_ptr>&, const QVariant& data );
    void albums( const QList<Hatchet::album_ptr>& );
    void done();

private:
    QSharedPointer< DatabaseCollection > m_collection;
    Hatchet::artist_ptr m_artist;

    unsigned int m_amount;
    DatabaseCommand_AllAlbums::SortOrder m_sortOrder;
    bool m_sortDescending;
    QString m_filter;
};

}

#endif // DATABASECOMMAND_ALLALBUMS_H
