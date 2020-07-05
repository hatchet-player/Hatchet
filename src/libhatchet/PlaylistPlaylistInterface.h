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

#ifndef PLAYLISTPLAYLISTINTERFACE_H
#define PLAYLISTPLAYLISTINTERFACE_H

#include <QObject>
#include <QList>
#include <QPointer>

#include "Typedefs.h"
#include "Result.h"
#include "PlaylistInterface.h"
#include "Query.h"

#include "DllMacro.h"

namespace Hatchet
{

class DLLEXPORT PlaylistPlaylistInterface : public Hatchet::PlaylistInterface
{
Q_OBJECT

public:
    PlaylistPlaylistInterface( Hatchet::Playlist* playlist );
    virtual ~PlaylistPlaylistInterface();

    virtual QList<Hatchet::query_ptr> tracks() const;

    virtual int trackCount() const;

    virtual void setCurrentIndex( qint64 index ) { Q_UNUSED( index ); }
    virtual Hatchet::result_ptr resultAt( qint64 index ) const { Q_UNUSED( index ); Q_ASSERT( false ); return Hatchet::result_ptr(); }
    virtual Hatchet::query_ptr queryAt( qint64 index ) const { Q_UNUSED( index ); Q_ASSERT( false ); return Hatchet::query_ptr(); }
    virtual qint64 indexOfResult( const Hatchet::result_ptr& result ) const { Q_UNUSED( result ); Q_ASSERT( false ); return -1; }
    virtual qint64 indexOfQuery( const Hatchet::query_ptr& query ) const { Q_UNUSED( query ); Q_ASSERT( false ); return -1; }

    virtual Hatchet::result_ptr currentItem() const { return m_currentItem; }
    virtual qint64 siblingIndex( int /*itemsAway*/, qint64 rootIndex = -1 ) const { Q_UNUSED( rootIndex ); return -1; }

    virtual PlaylistModes::RepeatMode repeatMode() const { return PlaylistModes::NoRepeat; }
    virtual bool shuffled() const { return false; }

public slots:
    virtual void setRepeatMode( PlaylistModes::RepeatMode ) {}
    virtual void setShuffled( bool ) {}

private:
    PlaylistPlaylistInterface();
    Q_DISABLE_COPY( PlaylistPlaylistInterface )

    QPointer< Hatchet::Playlist > m_playlist;

    result_ptr m_currentItem;
};

}

#endif // PLAYLISTPLAYLISTINTERFACE_H
