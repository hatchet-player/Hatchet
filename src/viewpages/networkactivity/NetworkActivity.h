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

#ifndef NETWORKACTIVITY_H
#define NETWORKACTIVITY_H

#include "NetworkActivityWidget.h"

#include "ViewPage.h"
#include "ViewPageLazyLoader.h"

#include "../ViewPageDllMacro.h"

class AnimatedSpinner;
class PlaylistModel;
class QModelIndex;
class QStandardItemModel;
class QSortFilterProxyModel;
namespace Ui
{
    class NetworkActivityWidget;
}

namespace Hatchet
{
namespace Widgets
{

class NetworkActivityWidgetPrivate;

class HATCHET_VIEWPAGE_EXPORT NetworkActivity : public Hatchet::ViewPageLazyLoader< NetworkActivityWidget >
{
Q_OBJECT
Q_INTERFACES( Hatchet::ViewPagePlugin )
Q_PLUGIN_METADATA( IID "org.hatchet-player.Player.ViewPagePlugin" )

public:
    NetworkActivity() {}
    virtual ~NetworkActivity() {}

    virtual const QString defaultName() { return QLatin1String( "networkactivity" ); }
    virtual QString title() const { return tr( "Trending" ); }
    virtual QString description() const { return tr( "What's hot amongst your friends" ); }
    virtual const QString pixmapPath() const { return ( RESPATH "images/trending.svg" ); }

    virtual int sortValue() { return 3; }
};

} // Widgets

} // Hatchet

#endif // NETWORKACTIVITY_H
