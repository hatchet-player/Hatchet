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

#ifndef TRACKPROXYMODELPLAYLISTINTERFACE_H
#define TRACKPROXYMODELPLAYLISTINTERFACE_H

#include "PlaylistInterface.h"
#include "playlist/PlayableModel.h"

#include "DllMacro.h"

#include <QSortFilterProxyModel>
#include <QPointer>

class PlayableProxyModel;

namespace Hatchet {

class DLLEXPORT PlayableProxyModelPlaylistInterface : public Hatchet::PlaylistInterface
{
Q_OBJECT

public:
    explicit PlayableProxyModelPlaylistInterface( PlayableProxyModel* proxyModel );
    virtual ~PlayableProxyModelPlaylistInterface();

    virtual QList<Hatchet::query_ptr> tracks() const;

    virtual int trackCount() const;

    virtual void setCurrentIndex( qint64 index );
    virtual Hatchet::result_ptr resultAt( qint64 index ) const;
    virtual Hatchet::query_ptr queryAt( qint64 index ) const;
    virtual qint64 indexOfResult( const Hatchet::result_ptr& result ) const;
    virtual qint64 indexOfQuery( const Hatchet::query_ptr& query ) const;

    virtual Hatchet::result_ptr currentItem() const;
    virtual qint64 siblingIndex( int itemsAway, qint64 rootIndex = -1 ) const;

    virtual QString filter() const;

    virtual PlaylistModes::RepeatMode repeatMode() const { return m_repeatMode; }
    virtual bool shuffled() const { return m_shuffled; }

public slots:
    virtual void setRepeatMode( Hatchet::PlaylistModes::RepeatMode mode ) { m_repeatMode = mode; emit repeatModeChanged( mode ); }
    virtual void setShuffled( bool enabled ) { m_shuffled = enabled; emit shuffleModeChanged( enabled ); }

private slots:
    void onCurrentIndexChanged();

protected:
    QPointer< PlayableProxyModel > m_proxyModel;

    PlaylistModes::RepeatMode m_repeatMode;
    bool m_shuffled;
    mutable QList< Hatchet::query_ptr > m_shuffleHistory;
    mutable QPersistentModelIndex m_shuffleCache;
};

} //ns

#endif // TRACKPROXYMODELPLAYLISTINTERFACE_H
