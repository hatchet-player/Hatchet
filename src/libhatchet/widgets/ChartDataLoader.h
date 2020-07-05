/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2011, Leo Franchi <lfranchi@kde.org>
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
#ifndef CHARTDATALOADER_H
#define CHARTDATALOADER_H

#include "infosystem/InfoSystem.h"

#include <QObject>

namespace Hatchet
{

/**
  Synchronous loading of track, artist, album objects from the db
  into their respective hatchet types. Move this object to a thread
  and listen to the result signals.
*/
class DLLEXPORT ChartDataLoader : public QObject
{
    Q_OBJECT
public:
    enum DataType {
        Track,
        Artist,
        Album
    };

    ChartDataLoader();

    void setType( DataType type ) { m_type = type; }
    void setData( const QList< InfoSystem::InfoStringHash >& data ) { m_data = data; }
    void setData( const QStringList& artists ) { m_artists = artists; }

public slots:
    void go();

signals:
    void tracks( Hatchet::ChartDataLoader*, const QList< Hatchet::query_ptr >& tracks );
    void artists( Hatchet::ChartDataLoader*, const QList< Hatchet::artist_ptr >& artists );
    void albums( Hatchet::ChartDataLoader*, const QList< Hatchet::album_ptr >& albums );


private:
    DataType m_type;
    QList<InfoSystem::InfoStringHash> m_data;
    QStringList m_artists;
};

}

#endif // CHARTDATALOADER_H
