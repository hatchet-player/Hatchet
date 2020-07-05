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
#ifndef HATCHET_DATABASECOMMAND_TRENDINGARTISTS_H
#define HATCHET_DATABASECOMMAND_TRENDINGARTISTS_H

#include "Artist.h"
#include "database/DatabaseCommand.h"

namespace Hatchet {

class DatabaseCommand_TrendingArtistsPrivate;

class DLLEXPORT DatabaseCommand_TrendingArtists : public Hatchet::DatabaseCommand
{
    Q_OBJECT
public:
    explicit DatabaseCommand_TrendingArtists( QObject* parent = 0 );
    virtual ~DatabaseCommand_TrendingArtists();

    virtual void exec( DatabaseImpl* );

    virtual bool doesMutates() const { return false; }
    virtual QString commandname() const { return "trendingartists"; }

    void setLimit( unsigned int amount );

signals:
    void done( const QList<QPair< double, Hatchet::artist_ptr > >& artists );

private:
    Q_DECLARE_PRIVATE( DatabaseCommand_TrendingArtists )

};

} // namespace Hatchet

#endif // HATCHET_DATABASECOMMAND_TRENDINGARTISTS_H
