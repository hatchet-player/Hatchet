/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2013, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef DATABASECOMMAND_UPDATESEARCHINDEX_H
#define DATABASECOMMAND_UPDATESEARCHINDEX_H

#include "database/DatabaseCommand.h"
#include "DllMacro.h"
#include <QPointer>

namespace Hatchet
{

struct IndexData
{
    unsigned int id;
    unsigned int artistId;
    QString artist;
    QString album;
    QString track;
};

class DLLEXPORT DatabaseCommand_UpdateSearchIndex : public DatabaseCommand
{
Q_OBJECT
public:
    explicit DatabaseCommand_UpdateSearchIndex();
    virtual ~DatabaseCommand_UpdateSearchIndex();

    virtual QString commandname() const { return "updatesearchindex"; }
    virtual bool doesMutates() const { return true; }
    virtual void exec( DatabaseImpl* db );
};

}

#endif // DATABASECOMMAND_UPDATESEARCHINDEX_H