/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2014,      Dominik Schmidt <domme@tomahawk-player.org>
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

#ifndef HATCHET_SCRIPTINFOPLUGIN_H
#define HATCHET_SCRIPTINFOPLUGIN_H

#include "../infosystem/InfoSystem.h"
#include "ScriptPlugin.h"

#include "DllMacro.h"


namespace Hatchet
{

class JSAccount;
class ScriptInfoPluginPrivate;
class ScriptObject;


class DLLEXPORT ScriptInfoPlugin : public Hatchet::InfoSystem::InfoPlugin, Hatchet::ScriptPlugin
{
Q_OBJECT

public:
    /**
     * @param id unique identifier to identify an infoplugin in its scope
     */
    ScriptInfoPlugin( const scriptobject_ptr& scriptObject, const QString& name );
    virtual ~ScriptInfoPlugin();

protected slots:
    void init() override;

    void getInfo( Hatchet::InfoSystem::InfoRequestData requestData ) override;
    void pushInfo( Hatchet::InfoSystem::InfoPushData pushData ) override;
    void notInCacheSlot( Hatchet::InfoSystem::InfoStringHash criteria, Hatchet::InfoSystem::InfoRequestData requestData ) override;

    void onGetInfoRequestDone( const QVariantMap& result );
    void onNotInCacheRequestDone( const QVariantMap& result );
    void onCoverArtReturned();

    // boilerplate: to be removed with Qt5 (can be put into ScriptPlugin)
    void onScriptObjectDeleted();

private:
    static QSet< Hatchet::InfoSystem::InfoType > parseSupportedTypes(const QVariant& variant);
    static QString serializeQVariantMap(const QVariantMap& map);
    static QVariantMap convertInfoStringHashToQVariantMap(const Hatchet::InfoSystem::InfoStringHash& hash);
    static Hatchet::InfoSystem::InfoStringHash convertQVariantMapToInfoStringHash( const QVariantMap& map );

    Q_DECLARE_PRIVATE( ScriptInfoPlugin )
    QScopedPointer<ScriptInfoPluginPrivate> d_ptr;
};

}; // ns: Hatchet

#endif // HATCHET_SCRIPTINFOPLUGIN_H
