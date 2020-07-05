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

#pragma once
#ifndef HATCHET_UTILS_HatchetLinkGeneratorPlugin_H
#define HATCHET_UTILS_HatchetLinkGeneratorPlugin_H

#include "LinkGeneratorPlugin.h"

#include "../DllMacro.h"
#include "../Typedefs.h"

namespace Hatchet {

class ScriptJob;

namespace Utils {

class DLLEXPORT HatchetLinkGeneratorPlugin : public LinkGeneratorPlugin
{
public:
    ScriptJob* openLink( const QString& title, const QString& artist, const QString& album ) const override;
    ScriptJob* openLink( const Hatchet::artist_ptr& artist ) const override;
    ScriptJob* openLink( const Hatchet::album_ptr& album ) const override;
    // echonest is dead, disable all echonest code
    // ScriptJob* openLink( const Hatchet::dynplaylist_ptr& playlist ) const override;

private:
    QString hostname() const;

};

} // namespace Utils
} // namespace Hatchet

#endif // HATCHET_UTILS_HatchetLinkGeneratorPlugin_H
