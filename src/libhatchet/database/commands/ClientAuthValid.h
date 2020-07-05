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

#ifndef DATABASECOMMAND_CLIENTAUTHVALID_H
#define DATABASECOMMAND_CLIENTAUTHVALID_H

#include "database/DatabaseCommand.h"
#include "DllMacro.h"

#include <QObject>

namespace Hatchet
{

class DLLEXPORT DatabaseCommand_ClientAuthValid : public DatabaseCommand
{
    Q_OBJECT
public:
    explicit DatabaseCommand_ClientAuthValid( QObject* parent = 0 )
            : DatabaseCommand( parent )
    {}

    explicit DatabaseCommand_ClientAuthValid( const QString& clientToken, QObject* parent = 0 );

    QString commandname() const { return "clientauthvalid"; }

    virtual void exec( DatabaseImpl* lib );
    virtual bool doesMutates() const { return false; }

signals:
    // if auth is invalid name is empty
    void authValid( const QString& clientToken, const QString& name, bool valid );

private:
    QString m_clientToken;
};

}

#endif // DATABASECOMMAND_CLIENTAUTHVALID_H
