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

#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include <QPixmap>

#include "Album.h"
#include "PlaylistInterface.h"
#include "database/commands/AllAlbums.h"
#include "PlayableModel.h"

#include "DllMacro.h"

class PlayableItem;
class QMetaData;

class DLLEXPORT AlbumModel : public PlayableModel
{
Q_OBJECT

public:
    explicit AlbumModel( QObject* parent = 0 );
    virtual ~AlbumModel();

    Hatchet::collection_ptr collection() const { return m_collection; }

    void addCollection( const Hatchet::collection_ptr& collection, bool overwrite = false );
    void addFilteredCollection( const Hatchet::collection_ptr& collection, unsigned int amount, Hatchet::DatabaseCommand_AllAlbums::SortOrder order, bool overwrite = false );

    PlayableItem* findItem( const Hatchet::artist_ptr& artist ) const;
    PlayableItem* findItem( const Hatchet::album_ptr& album ) const;

public slots:
    void addAlbums( const QList<Hatchet::album_ptr>& albums );
    void addArtists( const QList<Hatchet::artist_ptr>& artists );
    void addQueries( const QList<Hatchet::query_ptr>& queries );

signals:

private slots:
    void onSourceAdded( const Hatchet::source_ptr& source );
    void onCollectionChanged();

private:
    bool m_overwriteOnAdd;

    Hatchet::collection_ptr m_collection;
};

#endif // ALBUMMODEL_H
