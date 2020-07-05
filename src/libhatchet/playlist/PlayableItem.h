/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2012, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef PLAYABLEITEM_H
#define PLAYABLEITEM_H

#include <QAbstractItemModel>
#include <QHash>
#include <QPersistentModelIndex>
#include <QPixmap>

#include "Track.h"
#include "Typedefs.h"
#include "DllMacro.h"

class DLLEXPORT PlayableItem : public QObject
{
Q_OBJECT

public:
    ~PlayableItem();

    explicit PlayableItem( PlayableItem* parent = 0 );
    explicit PlayableItem( const Hatchet::artist_ptr& artist, PlayableItem* parent = 0, int row = -1 );
    explicit PlayableItem( const Hatchet::album_ptr& album, PlayableItem* parent = 0, int row = -1 );
    explicit PlayableItem( const Hatchet::result_ptr& result, PlayableItem* parent = 0, int row = -1 );
    explicit PlayableItem( const Hatchet::query_ptr& query, PlayableItem* parent = 0, int row = -1 );
    explicit PlayableItem( const Hatchet::plentry_ptr& entry, PlayableItem* parent = 0, int row = -1 );
    explicit PlayableItem( const Hatchet::source_ptr& source, PlayableItem* parent = 0, int row = -1 );

    const Hatchet::artist_ptr& artist() const { return m_artist; }
    const Hatchet::album_ptr& album() const { return m_album; }
    const Hatchet::query_ptr& query() const { return m_query; }
    const Hatchet::plentry_ptr& entry() const { return m_entry; }
    const Hatchet::source_ptr& source() const { return m_source; }
    const Hatchet::result_ptr& result() const;

    Hatchet::PlaybackLog playbackLog() const;
    void setPlaybackLog( const Hatchet::PlaybackLog& log );

    PlayableItem* parent() const { return m_parent; }
    void forceUpdate() { emit dataChanged(); }

    bool isPlaying() const { return m_isPlaying; }
    void setIsPlaying( bool b ) { m_isPlaying = b; emit dataChanged(); }
    bool fetchingMore() const { return m_fetchingMore; }
    void setFetchingMore( bool b ) { m_fetchingMore = b; }
    void requestRepaint() { emit dataChanged(); }

    QString name() const;
    QString artistName() const;
    QString albumName() const;

    QList<PlayableItem*> children;

    QPersistentModelIndex index;

signals:
    void dataChanged();

private slots:
    void onResultsChanged();

private:
    void init( int row = -1 );

    Hatchet::artist_ptr m_artist;
    Hatchet::album_ptr m_album;
    Hatchet::plentry_ptr m_entry;
    Hatchet::result_ptr m_result;
    Hatchet::query_ptr m_query;
    Hatchet::source_ptr m_source;

    PlayableItem* m_parent;
    bool m_fetchingMore = false;
    bool m_isPlaying = false;

    Hatchet::PlaybackLog m_playbackLog;
};

#endif // PLAYABLEITEM_H
