/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef RECENTLYPLAYEDMODEL_H
#define RECENTLYPLAYEDMODEL_H

#include <QList>
#include <QDate>
#include <QHash>

#include "Typedefs.h"
#include "PlaylistModel.h"
#include "Source.h"

#include "DllMacro.h"

class DLLEXPORT RecentlyPlayedModel : public PlayableModel
{
Q_OBJECT

public:
    explicit RecentlyPlayedModel( QObject* parent = 0, unsigned int maxItems = 0 );
    ~RecentlyPlayedModel();

    unsigned int limit() const { return m_limit; }
    void setLimit( unsigned int limit ) { m_limit = limit; }

    bool isTemporary() const;

public slots:
    void setSource( const Hatchet::source_ptr& source );
    void setDateFrom( const QDate& date );
    void setDateTo( const QDate& date );

private slots:
    void onSourcesReady();
    void onSourceAdded( const Hatchet::source_ptr& source );

    void onPlaybackFinished( const Hatchet::track_ptr& track, const Hatchet::PlaybackLog& log );
    void loadHistory();

    void onTracksLoaded( QList<Hatchet::track_ptr> tracks, QList<Hatchet::PlaybackLog> logs );

private:
    Hatchet::source_ptr m_source;
    unsigned int m_limit;
    QDate m_dateFrom;
    QDate m_dateTo;
};

#endif // RECENTLYPLAYEDMODEL_H
