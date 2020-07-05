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

#ifndef SCRIPTCOMMAND_ALLTRACKS_H
#define SCRIPTCOMMAND_ALLTRACKS_H

#include "Query.h"
#include "collection/TracksRequest.h"
#include "collection/Collection.h"
#include "resolvers/ScriptCommand.h"

namespace Hatchet
{

class ScriptCommand_AllTracks : public ScriptCommand, public Hatchet::TracksRequest
{
    Q_OBJECT
public:
    explicit ScriptCommand_AllTracks( const Hatchet::collection_ptr& collection,
                                      const Hatchet::album_ptr& album,
                                      QObject *parent = 0 );
    virtual ~ScriptCommand_AllTracks() {}

    void enqueue() override;

signals:
    void tracks( const QList< Hatchet::query_ptr >& ) override;
    void done() override;

protected:
    Q_INVOKABLE void exec() override;
    void reportFailure() override;

private slots:
    void onTracksJobDone( const QVariantMap& result );

private:
    Hatchet::collection_ptr m_collection;
    Hatchet::album_ptr m_album;
};

} // ns: Hatchet

#endif // SCRIPTCOMMAND_ALLTRACKS_H
