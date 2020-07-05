/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Teo Mrnjavac <teo@kde.org>
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

#ifndef DATABASECOMMAND_MODIFYINBOXENTRY_H
#define DATABASECOMMAND_MODIFYINBOXENTRY_H

#include "DatabaseCommand.h"

namespace Hatchet
{

class DatabaseCommand_ModifyInboxEntry : public DatabaseCommand
{
    Q_OBJECT
public:
    explicit DatabaseCommand_ModifyInboxEntry( const Hatchet::query_ptr& query, bool newValue, QObject *parent = 0 );

    virtual void exec( DatabaseImpl* dbi );
    virtual bool doesMutates() const { return true; }
    virtual bool groupable() const { return true; }
    virtual bool localOnly() const { return true; }
    virtual QString commandname() const { return "modifyinboxentry"; }

signals:
    void done();

private:
    Hatchet::query_ptr m_query;
    bool m_newValue;
};

}

#endif // DATABASECOMMAND_MODIFYINBOXENTRY_H
