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
#include "ScriptObject_p.h"

#include "ScriptAccount.h"


using namespace Hatchet;

ScriptObject::ScriptObject( const QString& id, ScriptAccount* parent )
    : QObject()
    , d_ptr( new ScriptObjectPrivate( this, id, parent ))
{
}


ScriptObject::~ScriptObject()
{
     //TODO: Album clears the ownRef wptr explicitly ... why?
}


void
ScriptObject::setWeakRef(const scriptobject_wptr& weakRef)
{
    Q_D( ScriptObject );
    d->ownRef = weakRef;
}


scriptobject_wptr
ScriptObject::weakRef() const
{
    Q_D( const ScriptObject );

    return d->ownRef;
}


ScriptJob*
ScriptObject::invoke( const QString& methodName, const QVariantMap& arguments )
{
    Q_D( ScriptObject );

    return d->scriptAccount->invoke( weakRef().toStrongRef(), methodName, arguments );
}


QVariant
ScriptObject::syncInvoke(const QString& methodName, const QVariantMap& arguments)
{
    Q_D( ScriptObject );

    return d->scriptAccount->syncInvoke( weakRef().toStrongRef(), methodName, arguments );
}


QString
ScriptObject::id() const
{
    Q_D( const ScriptObject );

    return d->id;
}


void
ScriptObject::startJob( ScriptJob* scriptJob )
{
    Q_D( const ScriptObject );

    d->scriptAccount->startJob( scriptJob );
}
