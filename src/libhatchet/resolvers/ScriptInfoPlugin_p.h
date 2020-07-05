/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2014,    Dominik Schmidt <domme@tomahawk-player.org>
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

#ifndef HATCHET_SCRIPTINFOPLUGIN_P_H
#define HATCHET_SCRIPTINFOPLUGIN_P_H

#include "ScriptInfoPlugin.h"

namespace  Hatchet
{

class ScriptInfoPluginPrivate
{
    friend class ScriptInfoPlugin;
public:
    ScriptInfoPluginPrivate( ScriptInfoPlugin* q )
        : q_ptr ( q )
    {
    }
    ScriptInfoPlugin* q_ptr;
    Q_DECLARE_PUBLIC ( ScriptInfoPlugin )

private:
    QMap< int, Hatchet::InfoSystem::InfoRequestData > requestDataCache;
    QMap< int, Hatchet::InfoSystem::InfoStringHash > criteriaCache;
};

} // ns: Hatchet

#endif // HATCHET_SCRIPTINFOPLUGIN_P_H
