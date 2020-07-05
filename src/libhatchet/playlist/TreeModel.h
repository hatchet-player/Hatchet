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

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QPixmap>

#include "Artist.h"
#include "Album.h"
#include "Query.h"
#include "Result.h"
#include "PlayableModel.h"
#include "PlaylistInterface.h"
#include "database/DatabaseCommand_AllArtists.h"

#include "DllMacro.h"
#include "Typedefs.h"

class QMetaData;

class PlayableItem;

class DLLEXPORT TreeModel : public PlayableModel
{
Q_OBJECT

public:
    explicit TreeModel( QObject* parent = 0 );
    virtual ~TreeModel();

    virtual Hatchet::ModelMode mode() const { return m_mode; }
    virtual void setMode( Hatchet::ModelMode mode );

    Hatchet::collection_ptr collection() const;

    void addCollection( const Hatchet::collection_ptr& collection );
    //TODO: Unused, but will be useful for supporting filtered queries. - Teo 1/2013
    //void addFilteredCollection( const Hatchet::collection_ptr& collection, unsigned int amount, DatabaseCommand_AllArtists::SortOrder order );

    void addArtists( const Hatchet::artist_ptr& artist );
    void fetchAlbums( const Hatchet::artist_ptr& artist );

    void getCover( const QModelIndex& index );

    virtual PlayableItem* itemFromResult( const Hatchet::result_ptr& result ) const;

    virtual QModelIndex indexFromArtist( const Hatchet::artist_ptr& artist ) const;
    virtual QModelIndex indexFromAlbum( const Hatchet::album_ptr& album ) const;
    virtual QModelIndex indexFromResult( const Hatchet::result_ptr& result ) const;
    virtual QModelIndex indexFromQuery( const Hatchet::query_ptr& query ) const;

public slots:
    void addAlbums( const QModelIndex& parent, const QList<Hatchet::album_ptr>& albums );
    void addTracks( const Hatchet::album_ptr& album, const QModelIndex& parent );

signals:
    void modeChanged( Hatchet::ModelMode mode );

protected:
    bool canFetchMore( const QModelIndex& parent ) const;
    void fetchMore( const QModelIndex& parent );

private slots:
    void onArtistsAdded( const QList<Hatchet::artist_ptr>& artists );
    void onAlbumsFound( const QList<Hatchet::album_ptr>& albums, Hatchet::ModelMode mode );
    void onTracksAdded( const QList<Hatchet::query_ptr>& tracks, const QModelIndex& index );

private:
    Hatchet::ModelMode m_mode;
    Hatchet::collection_ptr m_collection;

    QList<Hatchet::artist_ptr> m_artistsFilter;
};

#endif // ALBUMMODEL_H
