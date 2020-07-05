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

#ifndef DATABASECOMMAND_DELETEDYNAMICPLAYLIST_H
#define DATABASECOMMAND_DELETEDYNAMICPLAYLIST_H

#include "DeletePlaylist.h"
#include "Typedefs.h"

namespace Hatchet
{

class DatabaseCommand_DeleteDynamicPlaylist : public DatabaseCommand_DeletePlaylist
{
    Q_OBJECT
public:
    explicit DatabaseCommand_DeleteDynamicPlaylist( QObject* parent = 0 )
    : DatabaseCommand_DeletePlaylist( parent )
    {}

    explicit DatabaseCommand_DeleteDynamicPlaylist( const Hatchet::source_ptr& source, const QString& playlistguid );

    QString commandname() const { return "deletedynamicplaylist"; }

    virtual void exec( DatabaseImpl* lib );
    virtual void postCommitHook();
    virtual bool doesMutates() const { return true; }

};

}

#endif // DATABASECOMMAND_DELETEDYNAMICPLAYLIST_H
