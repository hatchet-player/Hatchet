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

#ifndef SCRIPTERRORSTATUSMESSAGE_H
#define SCRIPTERRORSTATUSMESSAGE_H

#include "ErrorStatusMessage.h"
#include "../resolvers/ScriptAccount.h"

#include "DllMacro.h"

class DLLEXPORT ScriptErrorStatusMessage : public ErrorStatusMessage
{
    Q_OBJECT
public:
    explicit ScriptErrorStatusMessage( const QString& scriptErrorMessage, Hatchet::ScriptAccount* );

    void activated() override;

private:
    QPointer< Hatchet::ScriptAccount > m_account;
};

#endif // SCRIPTERRORSTATUSMESSAGE_H
