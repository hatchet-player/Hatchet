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

#ifndef HATCHETARTISTPLAYLISTINTERFACE_H
#define HATCHETARTISTPLAYLISTINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QPointer>

#include "Artist.h"
#include "Typedefs.h"
#include "PlaylistInterface.h"
#include "DllMacro.h"

namespace Hatchet
{

class DLLEXPORT ArtistPlaylistInterface : public Hatchet::PlaylistInterface
{
Q_OBJECT

public:
    ArtistPlaylistInterface( Hatchet::Artist* artist, Hatchet::ModelMode mode, const Hatchet::collection_ptr& collection );
    virtual ~ArtistPlaylistInterface();

    virtual QList<Hatchet::query_ptr> tracks() const;

    virtual int trackCount() const { return m_queries.count(); }

    virtual void setCurrentIndex( qint64 index );
    virtual qint64 siblingIndex( int itemsAway, qint64 rootIndex = -1 ) const;
    virtual Hatchet::result_ptr resultAt( qint64 index ) const;
    virtual Hatchet::query_ptr queryAt( qint64 index ) const;
    virtual qint64 indexOfResult( const Hatchet::result_ptr& result ) const;
    virtual qint64 indexOfQuery( const Hatchet::query_ptr& query ) const;

    virtual Hatchet::result_ptr currentItem() const;

    virtual PlaylistModes::RepeatMode repeatMode() const { return PlaylistModes::NoRepeat; }
    virtual bool shuffled() const { return false; }

    virtual void setRepeatMode( PlaylistModes::RepeatMode ) {}
    virtual void setShuffled( bool ) {}

signals:
    void tracksLoaded( Hatchet::ModelMode mode, const Hatchet::collection_ptr& collection );

private slots:
    void onTracksLoaded( const QList< Hatchet::query_ptr >& tracks );
    void infoSystemInfo( Hatchet::InfoSystem::InfoRequestData requestData, QVariant output );
    void infoSystemFinished( const QString& infoId );

private:
    Q_DISABLE_COPY( ArtistPlaylistInterface )

    QList< Hatchet::query_ptr > m_queries;
    mutable result_ptr m_currentItem;

    bool m_infoSystemLoaded;
    bool m_databaseLoaded;

    Hatchet::ModelMode m_mode;
    Hatchet::collection_ptr m_collection;

    QPointer< Hatchet::Artist > m_artist;
};

}; // ns

#endif
