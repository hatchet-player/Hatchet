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

#ifndef HATCHETSOURCEPLAYLISTINTERFACE_H
#define HATCHETSOURCEPLAYLISTINTERFACE_H

#include <QObject>
#include <QPointer>

#include "Typedefs.h"
#include "PlaylistInterface.h"

#include "DllMacro.h"

namespace Hatchet
{

class DLLEXPORT SourcePlaylistInterface : public Hatchet::PlaylistInterface
{
Q_OBJECT

public:
    SourcePlaylistInterface( Hatchet::Source* source, Hatchet::PlaylistModes::LatchMode latchMode = PlaylistModes::StayOnSong );
    virtual ~SourcePlaylistInterface();

    QList<Hatchet::query_ptr> tracks() const;

    virtual int trackCount() const { return 1; }

    virtual void setCurrentIndex( qint64 index );
    virtual Hatchet::result_ptr resultAt( qint64 index ) const;
    virtual Hatchet::query_ptr queryAt( qint64 index ) const;
    virtual qint64 indexOfResult( const Hatchet::result_ptr& result ) const;
    virtual qint64 indexOfQuery( const Hatchet::query_ptr& query ) const { Q_UNUSED( query ); Q_ASSERT( false ); return -1; }

    virtual qint64 siblingIndex( int itemsAway, qint64 rootIndex = -1 ) const;
    virtual bool sourceValid() const;
    virtual bool hasNextResult() const;
    virtual Hatchet::result_ptr nextResult() const;
    virtual Hatchet::result_ptr currentItem() const;

    virtual PlaylistModes::RepeatMode repeatMode() const { return PlaylistModes::NoRepeat; }
    virtual PlaylistModes::SeekRestrictions seekRestrictions() const { return PlaylistModes::NoSeek; }
    virtual PlaylistModes::SkipRestrictions skipRestrictions() const { return PlaylistModes::NoSkipBackwards; }
    virtual PlaylistModes::RetryMode retryMode() const { return PlaylistModes::Retry; }
    virtual quint32 retryInterval() const { return 5000; }

    virtual void setLatchMode( PlaylistModes::LatchMode latchMode ) { m_latchMode = latchMode; emit latchModeChanged( latchMode ); }

    virtual bool shuffled() const { return false; }

    virtual QPointer< Hatchet::Source > source() const;

    virtual void reset();

public slots:
    virtual void setRepeatMode( PlaylistModes::RepeatMode ) {}
    virtual void setShuffled( bool ) {}
    virtual void audioPaused() { setLatchMode( PlaylistModes::StayOnSong ); }

private slots:
    void onSourcePlaybackStarted( const Hatchet::track_ptr& track );
    void resolvingFinished( bool hasResults );

private:
    QPointer< Hatchet::Source > m_source;
    mutable Hatchet::result_ptr m_currentItem;
    mutable bool m_gotNextItem;
};

}; // ns

#endif
