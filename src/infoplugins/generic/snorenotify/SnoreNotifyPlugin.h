/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013-2015, Hannah von Reth <vonreth@kde.org>
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef SNORENOTIFYPLUGIN_H
#define SNORENOTIFYPLUGIN_H

#include "../../InfoPluginDllMacro.h"

#include "infosystem/InfoSystem.h"
#include <libsnore/snore.h>

namespace Hatchet
{

namespace InfoSystem
{

class INFOPLUGINDLLEXPORT SnoreNotifyPlugin : public InfoPlugin
{
    Q_PLUGIN_METADATA( IID "org.hatchet-player.Player.InfoPlugin" )
    Q_OBJECT
    Q_INTERFACES( Hatchet::InfoSystem::InfoPlugin )

public:
    SnoreNotifyPlugin();
    virtual ~SnoreNotifyPlugin();


protected slots:
    virtual void init() {}

    virtual void getInfo( Hatchet::InfoSystem::InfoRequestData requestData )
    {
        Q_UNUSED( requestData );
    }

    virtual void pushInfo( Hatchet::InfoSystem::InfoPushData pushData );

    virtual void notInCacheSlot( Hatchet::InfoSystem::InfoStringHash criteria, Hatchet::InfoSystem::InfoRequestData requestData )
    {
        Q_UNUSED( criteria );
        Q_UNUSED( requestData );
    }

protected slots:
    void slotActionInvoked(Snore::Notification n);

private:
    void notifyUser( InfoType type, const QString &messageText, Snore::Icon icon );
    void addAlert( Hatchet::InfoSystem::InfoType type, const QString &title );
    Snore::Application m_application;
    Snore::Icon m_defaultIcon;
    QHash< Hatchet::InfoSystem::InfoType, Snore::Alert > m_alerts;

    void nowPlaying( const QVariant &input );
    void inboxReceived( const QVariant &input );
};

}

}

#endif // SNORENOTIFYPLUGIN_H
