/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2013     , Uwe L. Korn <uwelk@xhochy.com>
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

#ifndef REVISIONQUEUEITEM_H
#define REVISIONQUEUEITEM_H

#include "Typedefs.h"

namespace Hatchet {

struct RevisionQueueItem
{
public:
    QString newRev;
    QString oldRev;
    QList< plentry_ptr > entries;
    bool applyToTip;

    RevisionQueueItem( const QString& nRev, const QString& oRev, const QList< plentry_ptr >& e, bool latest );
};

} // Hatchet

#endif // REVISIONQUEUEITEM_H
