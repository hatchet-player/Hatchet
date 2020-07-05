/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2016, Dominik Schmidt <domme@tomahawk-player.org>
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

#include "ScriptErrorStatusMessage.h"
#include "../utils/Logger.h"

ScriptErrorStatusMessage::ScriptErrorStatusMessage( const QString& message, Hatchet::ScriptAccount* account )
  : ErrorStatusMessage( tr( "Script Error: %1" ).arg( message ) )
  , m_account( account )
{
}

void
ScriptErrorStatusMessage::activated()
{
    if ( m_account.isNull() )
        return;

    tDebug() << "ScriptErrorStatusMessage clicked: " << mainText() << m_account->name();
    m_account->showDebugger();
}

