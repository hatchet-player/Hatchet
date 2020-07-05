/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Uwe L. Korn <uwelk@xhochy.com>
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

#pragma once
#ifndef HATCHET_DATABASECOMMAND_CALCULATEPLAYTIME_H
#define HATCHET_DATABASECOMMAND_CALCULATEPLAYTIME_H

#include "database/DatabaseCommand.h"

namespace Hatchet {

class DatabaseCommand_CalculatePlaytimePrivate;

class DLLEXPORT DatabaseCommand_CalculatePlaytime : public Hatchet::DatabaseCommand
{
    Q_OBJECT
public:
    explicit DatabaseCommand_CalculatePlaytime( const playlist_ptr& playlist, QDateTime from, QDateTime to, QObject* parent = 0 );
    explicit DatabaseCommand_CalculatePlaytime( const playlist_ptr& playlist, const QStringList& plEntryIds, QDateTime from, QDateTime to, QObject* parent = 0 );
    explicit DatabaseCommand_CalculatePlaytime( const track_ptr& track, QDateTime from, QDateTime to, QObject* parent = 0 );
    explicit DatabaseCommand_CalculatePlaytime( const QList<track_ptr>& tracks, QDateTime from, QDateTime to, QObject* parent = 0 );
    explicit DatabaseCommand_CalculatePlaytime( const query_ptr& query, QDateTime from, QDateTime to, QObject* parent = 0 );
    explicit DatabaseCommand_CalculatePlaytime( const QList<query_ptr>& queries, QDateTime from, QDateTime to, QObject* parent = 0 );
    virtual ~DatabaseCommand_CalculatePlaytime();

    virtual void exec( DatabaseImpl* dbi );

    virtual bool doesMutates() const { return false; }
    virtual QString commandname() const { return "calculateplaytime"; }


signals:
    void done( uint playtime );
    void done( const Hatchet::playlist_ptr& playlist, uint playtime );

private:
    Q_DECLARE_PRIVATE( DatabaseCommand_CalculatePlaytime )
};

} // namespace Hatchet

#endif // HATCHET_DATABASECOMMAND_CALCULATEPLAYTIME_H
