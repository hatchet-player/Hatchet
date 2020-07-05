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

#ifndef HATCHET_DATABASECOMMAND_TRENDINGTRACKS_H
#define HATCHET_DATABASECOMMAND_TRENDINGTRACKS_H

#include "Track.h"
#include "database/DatabaseCommand.h"

namespace Hatchet {

class DatabaseCommand_TrendingTracksPrivate;

/**
 * Find tracks that trend among your friends.
 *
 * At the moment the most trending tracks are those with the highest quotient of
 * plays in the last week and the week before with a penalty applied to those with
 * a low playcount.
 *
 * The exact calculation is done as follows:
 *
 * w_1(t) := playcount this week of track t
 * w_2(t) := playcount one week before of track t
 * p := active peers (with at least one play) in the last week
 * trending(track) = (w_1(t) / w_2(t)) * (1 - p / (4 * min(w_1(t), w_2(t))))
 */
class DLLEXPORT DatabaseCommand_TrendingTracks : public Hatchet::DatabaseCommand
{
    Q_OBJECT
public:
    explicit DatabaseCommand_TrendingTracks( QObject* parent = 0 );
    virtual ~DatabaseCommand_TrendingTracks();

    virtual void exec( DatabaseImpl* );

    virtual bool doesMutates() const { return false; }
    virtual QString commandname() const { return "trendingtracks"; }

    void setLimit( unsigned int amount );

signals:
    void done( const QList<QPair< double, Hatchet::track_ptr > >& tracks );

private:
    Q_DECLARE_PRIVATE( DatabaseCommand_TrendingTracks )
};

} // namespace Hatchet

#endif // HATCHET_DATABASECOMMAND_TRENDINGTRACKS_H
