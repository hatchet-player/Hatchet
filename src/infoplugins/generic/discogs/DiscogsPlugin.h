/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012 Leo Franchi <lfranchi@kde.org>
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

#ifndef DISCOGS_PLUGIN_H
#define DISCOGS_PLUGIN_H

#include "Typedefs.h"
#include "infosystem/InfoSystem.h"
#include "infosystem/InfoSystemWorker.h"

#include "../../InfoPluginDllMacro.h"

class QNetworkReply;

namespace Hatchet
{

namespace InfoSystem
{

class INFOPLUGINDLLEXPORT DiscogsPlugin : public InfoPlugin
{
    Q_PLUGIN_METADATA( IID "org.hatchet-player.Player.InfoPlugin" )
    Q_OBJECT
    Q_INTERFACES( Hatchet::InfoSystem::InfoPlugin )

public:
    DiscogsPlugin();
    virtual ~DiscogsPlugin();

protected slots:
    virtual void init() {}
    virtual void getInfo( Hatchet::InfoSystem::InfoRequestData requestData );
    virtual void notInCacheSlot( InfoStringHash criteria, InfoRequestData requestData );

    virtual void pushInfo( Hatchet::InfoSystem::InfoPushData ) {}
private slots:
    void albumSearchSlot( const Hatchet::InfoSystem::InfoRequestData& , QNetworkReply* );
    void albumInfoSlot( const Hatchet::InfoSystem::InfoRequestData& , QNetworkReply* );

private:
    bool isValidTrackData( Hatchet::InfoSystem::InfoRequestData requestData );
};

}

}

#endif
