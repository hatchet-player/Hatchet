/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2011, Leo Franchi <lfranchi@kde.org>
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

#include "LocalCollection.h"

#include "utils/Logger.h"
#include "utils/HatchetUtilsGui.h"

#include "PlaylistEntry.h"
#include "SourceList.h"
#include "ViewManager.h"
#include <HatchetSettings.h>


using namespace Hatchet;

LocalCollection::LocalCollection( const Hatchet::source_ptr& source, QObject* parent )
    : DatabaseCollection( source, parent )
{
}


QString
LocalCollection::prettyName() const
{
    return tr( "Your Collection" );
}
