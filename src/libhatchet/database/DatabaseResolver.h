/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef DATABASERESOLVER_H
#define DATABASERESOLVER_H

#include "resolvers/Resolver.h"
#include "Result.h"
#include "Artist.h"
#include "Album.h"

#include "DllMacro.h"

class DLLEXPORT DatabaseResolver : public Hatchet::Resolver
{
Q_OBJECT

public:
    explicit DatabaseResolver( int weight );

    QString name() const override;
    virtual unsigned int weight() const override{ return m_weight; }
    virtual unsigned int timeout() const override{ return 0; }

public slots:
    virtual void resolve( const Hatchet::query_ptr& query ) override;

private slots:
    void gotResults( const Hatchet::QID qid, QList< Hatchet::result_ptr> results );
    void gotAlbums( const Hatchet::QID qid, QList< Hatchet::album_ptr> albums );
    void gotArtists( const Hatchet::QID qid, QList< Hatchet::artist_ptr> artists );

private:
    int m_weight;
};

#endif // DATABASERESOLVER_H
