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

#ifndef HATCHET_SCRIPTLINKGENERATORPLUGIN_H
#define HATCHET_SCRIPTLINKGENERATORPLUGIN_H

#include "../resolvers/ScriptPlugin.h"
#include "../utils/LinkGeneratorPlugin.h"

#include <QObject>

#include "DllMacro.h"

namespace Hatchet
{

class ScriptObject;
class ScriptLinkGeneratorPluginPrivate;

class DLLEXPORT ScriptLinkGeneratorPlugin : public QObject, public ScriptPlugin, public Utils::LinkGeneratorPlugin
{
Q_OBJECT

public:
    ScriptLinkGeneratorPlugin( const scriptobject_ptr& scriptObject );
    virtual ~ScriptLinkGeneratorPlugin();

    ScriptJob* openLink( const QString& title, const QString& artist, const QString& album ) const override;
    ScriptJob* openLink( const artist_ptr& artist ) const override;
    ScriptJob* openLink( const album_ptr& album ) const override;
    ScriptJob* openLink( const dynplaylist_ptr& playlist ) const override;

private:
    Q_DECLARE_PRIVATE( ScriptLinkGeneratorPlugin )
    QScopedPointer<ScriptLinkGeneratorPluginPrivate> d_ptr;
};

}; // ns: Hatchet

#endif // HATCHET_SCRIPTLINKGENERATORPLUGIN_H
