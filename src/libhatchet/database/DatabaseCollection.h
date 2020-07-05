/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi            <lfranchi@kde.org>
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

#ifndef DATABASECOLLECTION_H
#define DATABASECOLLECTION_H

#include "collection/Collection.h"
#include "DllMacro.h"
#include "Source.h"
#include "Typedefs.h"

#include <QDir>


namespace Hatchet
{

class DLLEXPORT DatabaseCollection : public Hatchet::Collection
{
Q_OBJECT

public:
    explicit DatabaseCollection( const Hatchet::source_ptr& source, QObject* parent = nullptr );
    virtual ~DatabaseCollection()
    {
        qDebug() << Q_FUNC_INFO;
    }

    BackendType backendType() const override { return DatabaseCollectionType; }

    bool isOnline() const override;
    bool isLocal() const override { return source()->isLocal(); }

    using Collection::source;

    void loadPlaylists() override;
    void loadAutoPlaylists() override;
    void loadStations() override;

    QList< Hatchet::playlist_ptr > playlists() override;
    QList< Hatchet::dynplaylist_ptr > autoPlaylists() override;
    QList< Hatchet::dynplaylist_ptr > stations() override;

    Hatchet::ArtistsRequest* requestArtists() override;
    Hatchet::AlbumsRequest*  requestAlbums( const Hatchet::artist_ptr& artist ) override;
    Hatchet::TracksRequest*  requestTracks( const Hatchet::album_ptr& album ) override;

    int trackCount() const override;
    QPixmap icon( const QSize& size ) const override;

    // Resolver interface
    unsigned int weight() const override;
    unsigned int timeout() const override;
    void resolve( const Hatchet::query_ptr& query ) override;

public slots:
    virtual void addTracks( const QList<QVariant>& newitems );
    virtual void removeTracks( const QDir& dir );

private slots:
    void stationCreated( const Hatchet::source_ptr& source, const QVariantList& data );
    void autoPlaylistCreated( const Hatchet::source_ptr& source, const QVariantList& data );
};

}

#endif // DATABASECOLLECTION_H
