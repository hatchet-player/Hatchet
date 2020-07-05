/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2014, Dominik Schmidt <domme@tomahawk-player.org>
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

#include "SyncScriptJob.h"

#include "../Typedefs.h"
#include "ScriptObject.h"

Tomahawk::SyncScriptJob::SyncScriptJob( const QVariantMap& resultData )
    : ScriptJob( QString(), scriptobject_ptr(), QString() )
{
    m_data = resultData;
}


void
Tomahawk::SyncScriptJob::start()
{
    QMetaObject::invokeMethod( this, "reportResultsMap", Qt::QueuedConnection, Q_ARG( QVariantMap, m_data.toMap() ) );
}
