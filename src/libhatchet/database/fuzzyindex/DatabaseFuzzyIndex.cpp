/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include "DatabaseFuzzyIndex.h"

#include "database/DatabaseImpl.h"
#include "database/Database.h"
#include "utils/HatchetUtils.h"

#include <QDir>


namespace Hatchet {

static QString s_indexPathName = "hatchet.lucene";

DatabaseFuzzyIndex::DatabaseFuzzyIndex( QObject* parent, bool wipe )
    : FuzzyIndex( parent, s_indexPathName, wipe )
{
}


void
DatabaseFuzzyIndex::updateIndex()
{
    Hatchet::DatabaseCommand* cmd = new Hatchet::DatabaseCommand_UpdateSearchIndex();
    Hatchet::Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );
}


void
DatabaseFuzzyIndex::wipeIndex()
{
    HatchetUtils::removeDirectory( HatchetUtils::appDataDir().absoluteFilePath( s_indexPathName ) );
}

} // namespace Hatchet
