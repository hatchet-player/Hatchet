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

#pragma once
#ifndef DATABASECOMMAND_LOADALLSOURCES_H
#define DATABASECOMMAND_LOADALLSOURCES_H

#include <QObject>
#include <QVariantMap>

#include "DatabaseCommand.h"
#include "Typedefs.h"

#include "DllMacro.h"

namespace Hatchet
{

class DLLEXPORT DatabaseCommand_LoadAllSources : public DatabaseCommand
{
Q_OBJECT

public:
    explicit DatabaseCommand_LoadAllSources( QObject* parent = 0 );

    virtual void exec( DatabaseImpl* );
    virtual bool doesMutates() const { return false; }
    virtual QString commandname() const { return "loadallsources"; }

signals:
    void done( const QList< Hatchet::source_ptr >& sources );
};

} // namespace Hatchet

#endif // DATABASECOMMAND_LOADALLSOURCES_H
