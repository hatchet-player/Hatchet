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

#ifndef DATABASECOMMAND_RESOLVE_H
#define DATABASECOMMAND_RESOLVE_H

#include "database/DatabaseCommand.h"
#include "database/DatabaseImpl.h"
#include "Result.h"
#include "Artist.h"
#include "Album.h"

#include <QVariant>

#include "DllMacro.h"

namespace Hatchet
{

class DLLEXPORT DatabaseCommand_Resolve : public DatabaseCommand
{
Q_OBJECT
public:
    explicit DatabaseCommand_Resolve( const Hatchet::query_ptr& query );
    virtual ~DatabaseCommand_Resolve();

    QString commandname() const override { return "dbresolve"; }
    bool doesMutates() const override { return false; }

    void exec( DatabaseImpl *lib ) override;

signals:
    void results( Hatchet::QID qid, QList<Hatchet::result_ptr> results );
    void albums( Hatchet::QID qid, QList<Hatchet::album_ptr> albums );
    void artists( Hatchet::QID qid, QList<Hatchet::artist_ptr> artists );

private:
    DatabaseCommand_Resolve();

    void fullTextResolve( DatabaseImpl* lib );
    void resolve( DatabaseImpl* lib );

    Hatchet::query_ptr m_query;
};

}

#endif // DATABASECOMMAND_RESOLVE_H
