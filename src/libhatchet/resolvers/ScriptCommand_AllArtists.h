/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Teo Mrnjavac <teo@kde.org>
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

#ifndef SCRIPTCOMMAND_ALLARTISTS_H
#define SCRIPTCOMMAND_ALLARTISTS_H

#include "Artist.h"
#include "collection/ArtistsRequest.h"
#include "collection/Collection.h"
#include "resolvers/ScriptCommand.h"

namespace Hatchet
{

class ScriptCommand_AllArtists : public ScriptCommand, public Hatchet::ArtistsRequest
{
Q_OBJECT
    friend class ScriptCommand_AllAlbums;

public:
    explicit ScriptCommand_AllArtists( const Hatchet::collection_ptr& collection,
                                       QObject* parent = nullptr );
    virtual ~ScriptCommand_AllArtists() {}

    void enqueue() override;

    void setFilter( const QString& filter ) override;

signals:
    void artists( const QList< Hatchet::artist_ptr >& ) override;
    void done() override;

protected:
    void exec() override;
    void reportFailure() override;

private slots:
    void onArtistsJobDone( const QVariantMap& result );

private:
    static QList< Hatchet::artist_ptr > parseArtistVariantList( const QVariantList& reslist );

    Hatchet::collection_ptr m_collection;
    QString m_filter;
};

} // ns: Hatchet

#endif // SCRIPTCOMMAND_ALLARTISTS_H
