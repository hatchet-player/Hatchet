/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2014, Dominik Schmidt <domme@tomahawk-player.org>
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
#ifndef HATCHET_SCRIPTPLUGIN_H
#define HATCHET_SCRIPTPLUGIN_H

#include "ScriptObject.h"
#include "../DllMacro.h"

#include <QPointer>

namespace Hatchet {

class ScriptObject;

class DLLEXPORT ScriptPlugin
{
public:
    ScriptPlugin( const scriptobject_ptr& object );
    virtual ~ScriptPlugin();

    scriptobject_ptr scriptObject() const;

protected: // TODO: pimple
    scriptobject_ptr m_scriptObject;

};

} // ns: Hatchet

#endif // HATCHET_SCRIPTPLUGIN_H
