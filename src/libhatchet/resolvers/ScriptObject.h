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

#ifndef HATCHET_SCRIPTOBJECT_H
#define HATCHET_SCRIPTOBJECT_H

#include "../Typedefs.h"

#include <QObject>
#include <QVariantMap>

#include "DllMacro.h"

namespace Hatchet
{

class ScriptAccount;
class ScriptObjectPrivate;
class ScriptJob;

class DLLEXPORT ScriptObject : public QObject
{
friend class JSAccount;
friend class ScriptJob;

public:
    ScriptObject( const QString& id, ScriptAccount* parent );
    virtual ~ScriptObject();

    QString id() const;

    void setWeakRef( const scriptobject_wptr& weakRef );
    scriptobject_wptr weakRef() const;

    ScriptJob* invoke( const QString& methodName, const QVariantMap& arguments = QVariantMap() );

    /**
     * Avoid using this if possible, it's blocking and can only be used from the gui thread
     */
    QVariant syncInvoke( const QString& methodName, const QVariantMap& arguments = QVariantMap() );

protected:
    void startJob( ScriptJob* scriptJob );

private:
    Q_DECLARE_PRIVATE( ScriptObject )
    QScopedPointer<ScriptObjectPrivate> d_ptr;
};

}; // ns: Hatchet

#endif // HATCHET_SCRIPTOBJECT_H
