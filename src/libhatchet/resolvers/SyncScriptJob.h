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
#ifndef HATCHET_SYNCSCRIPTJOB_H
#define HATCHET_SYNCSCRIPTJOB_H

#include "ScriptJob.h"

#include "../DllMacro.h"
#include "../Typedefs.h"

namespace Hatchet {

class SyncScriptJob : public ScriptJob
{
Q_OBJECT

public:
    SyncScriptJob( const QVariantMap& resultData );

    void start() override;
};

} // namespace Hatchet

#endif // HATCHET_SYNCSCRIPTJOB_H
