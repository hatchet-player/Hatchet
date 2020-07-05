/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef METAPLAYLISTINTERFACE_H
#define METAPLAYLISTINTERFACE_H

#include <QtCore/QModelIndex>

#include "PlaylistInterface.h"
#include "playlist/PlayableItem.h"
#include "Typedefs.h"
#include "DllMacro.h"

namespace Hatchet
{

class DLLEXPORT MetaPlaylistInterface : public PlaylistInterface
{
Q_OBJECT

public:
    explicit MetaPlaylistInterface();
    virtual ~MetaPlaylistInterface();

    void addChildInterface( const Hatchet::playlistinterface_ptr& interface );
    void removeChildInterface( const Hatchet::playlistinterface_ptr& interface );

    virtual QList< Hatchet::query_ptr > tracks() const;
    virtual int trackCount() const;
    virtual Hatchet::result_ptr currentItem() const;
    virtual qint64 siblingIndex( int itemsAway, qint64 rootIndex = -1 ) const;
    virtual Hatchet::result_ptr resultAt( qint64 index ) const;
    virtual Hatchet::query_ptr queryAt( qint64 index ) const;
    virtual qint64 indexOfResult( const Hatchet::result_ptr& result ) const;
    virtual qint64 indexOfQuery( const Hatchet::query_ptr& query ) const;

    virtual PlaylistModes::RepeatMode repeatMode() const;
    virtual bool shuffled() const;

    virtual bool hasChildInterface( const Hatchet::playlistinterface_ptr& interface );

public slots:
    virtual void setRepeatMode( PlaylistModes::RepeatMode mode );
    virtual void setShuffled( bool enabled );

private:
    QList< Hatchet::playlistinterface_ptr > m_childInterfaces;
};

}

#endif // METAPLAYLISTINTERFACE_H
