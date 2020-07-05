/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2014, Dominik Schmidt <domme@tomahawk-player.org>
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

#include "LinkGeneratorPlugin.h"

#include "LinkGenerator.h"

#include "../Query.h"
#include "../Track.h"
#include "../Artist.h"
#include "../Album.h"

Hatchet::Utils::LinkGeneratorPlugin::~LinkGeneratorPlugin()
{
    // do this on destroyed() if you ever make this a QObject
    LinkGenerator::instance()->removePlugin( this );
}


Hatchet::ScriptJob*
Hatchet::Utils::LinkGeneratorPlugin::openLink(const QString&, const QString&, const QString&) const
{
    return nullptr;
}


Hatchet::ScriptJob*
Hatchet::Utils::LinkGeneratorPlugin::openLink( const Hatchet::query_ptr& query ) const
{
    QString title = query->track()->track();
    QString artist = query->track()->artist();
    QString album = query->track()->album();

    return openLink( title, artist, album );
}


Hatchet::ScriptJob*
Hatchet::Utils::LinkGeneratorPlugin::openLink(const Hatchet::artist_ptr&) const
{
    return nullptr;
}


Hatchet::ScriptJob*
Hatchet::Utils::LinkGeneratorPlugin::openLink(const Hatchet::album_ptr&) const
{
    return nullptr;
}


Hatchet::ScriptJob*
Hatchet::Utils::LinkGeneratorPlugin::openLink(const Hatchet::dynplaylist_ptr&) const
{
    return nullptr;
}
