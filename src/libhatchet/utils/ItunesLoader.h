/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Hugo Lindström <hugolm84@gmail.com>
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
 *
 */

#ifndef __ITUNESLOADER__
#define __ITUNESLOADER__


#include "DllMacro.h"
#include "Typedefs.h"
#include "Query.h"
#include <QMap>
#include <QStringList>

namespace Hatchet
{

class DLLEXPORT ItunesLoader : public QObject
{
    Q_OBJECT
public:
    explicit ItunesLoader( const QString& input, QObject* parent = 0 );
    ~ItunesLoader(){}

private:
    void parseTracks( const QVariantMap& tracks );
    void parsePlaylists( const QVariantList& playlists );

    QString m_itunesLibFile;
    QStringList m_ignoreFields;

    QMap< QString, QList<Hatchet::query_ptr > > m_playlists;
    QMap< int, Hatchet::query_ptr > m_tracks;
};

}
#endif


