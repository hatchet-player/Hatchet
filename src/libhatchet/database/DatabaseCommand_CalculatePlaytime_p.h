/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Uwe L. Korn <uwelk@xhochy.com>
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

#pragma once
#ifndef DATABASECOMMAND_CALCULATEPLAYTIME_P_H
#define DATABASECOMMAND_CALCULATEPLAYTIME_P_H

#include "database/DatabaseCommand_p.h"
#include "database/DatabaseCommand_CalculatePlaytime.h"

#include <QDateTime>
#include <QStringList>

namespace Hatchet
{

class DatabaseCommand_CalculatePlaytimePrivate : public DatabaseCommandPrivate
{
    DatabaseCommand_CalculatePlaytimePrivate( DatabaseCommand_CalculatePlaytime* q, QDateTime _from, QDateTime _to )
        : DatabaseCommandPrivate( q )
        , from( _from )
        , to( _to )
    {
    }

    Q_DECLARE_PUBLIC( DatabaseCommand_CalculatePlaytime )

private:
    QDateTime from;
    QDateTime to;
    QStringList plEntryIds;
    QStringList trackIds;
    Hatchet::playlist_ptr playlist;
};

}

#endif // DATABASECOMMAND_CALCULATEPLAYTIME_P_H
