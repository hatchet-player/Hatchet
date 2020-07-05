/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Dominik Schmidt <domme@tomahawk-player.org>
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

#ifndef HATCHET_TESTDATABASE_H
#define HATCHET_TESTDATABASE_H

#include <QtTest>

#include "database/Database.h"
#include "database/DatabaseCommand_LogPlayback.h"


class TestDatabaseCommand : public Hatchet::DatabaseCommand
{
Q_OBJECT
    virtual QString commandname() const { return "TestCommand"; }
};

class TestDatabase : public QObject
{
    Q_OBJECT
private:
    Hatchet::Database* db;

private slots:
    void initTestCase()
    {
        db = new Hatchet::Database("test");
    }

    void cleanupTestCase()
    {
        delete db;
    }

    void testFactories()
    {
        Hatchet::dbcmd_ptr command;

        // can we check that his ASSERTs?, it's a build in type, one must not register it again
        // db->registerCommand<DatabaseCommand_LogPlayback>();

        // check that if we request a factory for LogPlayback it really creates a LogPlayback object
        command = db->commandFactory<Hatchet::DatabaseCommand_LogPlayback>()->newInstance();
        Hatchet::DatabaseCommand_LogPlayback* lpCmd =  qobject_cast< Hatchet::DatabaseCommand_LogPlayback* >( command.data() );
        QVERIFY( lpCmd );

        // try to handle a third party database command

        // test no command factory is available until now
        QVERIFY( !db->commandFactory<TestDatabaseCommand>() );

        // register it
        db->registerCommand<TestDatabaseCommand>();

        // make sure it's available now
        command = db->commandFactory<TestDatabaseCommand>()->newInstance();
        TestDatabaseCommand* tCmd = qobject_cast< TestDatabaseCommand* >( command.data() );
        QVERIFY( tCmd );
    }
};

#endif // HATCHET_TESTDATABASE_H
