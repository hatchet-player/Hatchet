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

#ifndef HATCHET_DATABASEFUZZYINDEX_H
#define HATCHET_DATABASEFUZZYINDEX_H

#include "FuzzyIndex.h"

namespace Hatchet {

class DatabaseFuzzyIndex : public FuzzyIndex
{
public:
    explicit DatabaseFuzzyIndex( QObject* parent, bool wipe = false );

    virtual void updateIndex();
    static void wipeIndex();
};

} // namespace Hatchet

#endif // HATCHET_DATABASEFUZZYINDEX_H
