/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
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

#ifndef HATCHET_GUI_HELPERS_H
#define HATCHET_GUI_HELPERS_H

#include "DllMacro.h"

class QWidget;
namespace Hatchet {
    namespace Accounts {
        class AccountFactory;
        class Account;
    }
}

namespace HatchetUtils
{
    DLLEXPORT void createAccountFromFactory( Hatchet::Accounts::AccountFactory*, QWidget* parent );
    DLLEXPORT void openAccountConfig( Hatchet::Accounts::Account*, QWidget* parent, bool showDelete = false );
}

#endif
