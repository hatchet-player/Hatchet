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

#ifndef SCRIPTCOMMANDQUEUE_H
#define SCRIPTCOMMANDQUEUE_H

#include "ScriptCommand.h"

#include <QQueue>
#include <QSharedPointer>
#include <QTimer>
#include <QMetaType>
#include <QMutex>

namespace Hatchet
{

class ScriptCommandQueue : public QObject
{
    Q_OBJECT
public:
    explicit ScriptCommandQueue( QObject* parent = 0 );
    virtual ~ScriptCommandQueue() {}

    void enqueue( const QSharedPointer< ScriptCommand >& req );

private slots:
    void nextCommand();
    void onCommandDone();
    void onTimeout();

private:
    QQueue< QSharedPointer< ScriptCommand > > m_queue;
    QTimer* m_timer;
    QMutex m_mutex;
};

} // ns: Hatchet

Q_DECLARE_METATYPE( QSharedPointer< Hatchet::ScriptCommand > )

#endif // SCRIPTCOMMANDQUEUE_H
