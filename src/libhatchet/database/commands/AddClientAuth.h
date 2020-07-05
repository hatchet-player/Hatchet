/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef DATABASECOMMAND_ADDCLIENTAUTH_H
#define DATABASECOMMAND_ADDCLIENTAUTH_H

#include "database/DatabaseCommand.h"
#include "DllMacro.h"

#include <QObject>

namespace Hatchet
{

class DatabaseImpl;

class DLLEXPORT DatabaseCommand_AddClientAuth : public DatabaseCommand
{
    Q_OBJECT
public:
    explicit DatabaseCommand_AddClientAuth( QObject* parent = 0 )
            : DatabaseCommand( parent )
    {}

    explicit DatabaseCommand_AddClientAuth( const QString& clientToken, const QString& website, const QString& name, const QString& userAgent, QObject* parent = 0 );

    QString commandname() const { return "addclientauth"; }

    virtual void exec( DatabaseImpl* lib );
    virtual bool doesMutates() const { return true; }

private:
    QString m_clientToken, m_website, m_name, m_userAgent;
};

}

#endif // DATABASECOMMAND_ADDCLIENTAUTH_H
