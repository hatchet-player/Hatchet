/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef DATABASECOMMAND_DIRMTIMES_H
#define DATABASECOMMAND_DIRMTIMES_H

#include <QObject>
#include <QVariantMap>
#include <QDir>
#include <QMap>

#include "database/DatabaseCommand.h"

#include "DllMacro.h"

// Not loggable, mtimes only used to speed up our local scanner.

namespace Hatchet
{

class DLLEXPORT DatabaseCommand_DirMtimes : public DatabaseCommand
{
Q_OBJECT

public:
    explicit DatabaseCommand_DirMtimes( const QString& prefix = QString(), QObject* parent = 0 )
        : DatabaseCommand( parent ), m_prefix( prefix ), m_update( false )
    {}

    explicit DatabaseCommand_DirMtimes( const QStringList& prefixes, QObject* parent = 0 )
    : DatabaseCommand( parent ), m_prefixes( prefixes ), m_update( false )
    {}

    explicit DatabaseCommand_DirMtimes( QMap<QString, unsigned int> tosave, QObject* parent = 0 )
        : DatabaseCommand( parent ), m_update( true ), m_tosave( tosave )
    {}

    virtual void exec( DatabaseImpl* );
    virtual bool doesMutates() const { return m_update; }
    virtual QString commandname() const { return "dirmtimes"; }

signals:
    void done( const QMap<QString, unsigned int>& );

public slots:

private:
    void execSelectPath( DatabaseImpl *dbi, const QDir& path, QMap<QString, unsigned int> &mtimes );

    void execSelect( DatabaseImpl* dbi );
    void execUpdate( DatabaseImpl* dbi );
    QString m_prefix;
    QStringList m_prefixes;
    bool m_update;
    QMap<QString, unsigned int> m_tosave;
};

}

#endif // DATABASECOMMAND_DIRMTIMES_H
