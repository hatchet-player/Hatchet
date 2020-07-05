/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2014,    Dominik Schmidt <domme@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TOMAHAWK_SCRIPTOBJECT_P_H
#define TOMAHAWK_SCRIPTOBJECT_P_H

#include "ScriptObject.h"

namespace  Tomahawk
{

class ScriptObjectPrivate
{
    friend class ScriptObject;
public:
    ScriptObjectPrivate( ScriptObject* q, const QString& id, ScriptAccount* scriptAccount )
        : q_ptr ( q )
        , id( id )
        , scriptAccount( scriptAccount )
    {
    }
    ScriptObject* q_ptr;
    Q_DECLARE_PUBLIC ( ScriptObject )

private:
    QString id;
    ScriptAccount* scriptAccount;
    scriptobject_wptr ownRef;
};

} // ns: Tomahawk

#endif // TOMAHAWK_SCRIPTOBJECT_P_H
