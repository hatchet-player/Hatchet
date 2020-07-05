/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
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

#ifndef ROVIPLUGIN_H
#define ROVIPLUGIN_H

#include "infosystem/InfoSystem.h"

#include "../../InfoPluginDllMacro.h"


#include <QNetworkReply>

class QNetworkAccessManager;

namespace Hatchet
{

namespace InfoSystem
{

class INFOPLUGINDLLEXPORT RoviPlugin : public InfoPlugin
{
    Q_PLUGIN_METADATA( IID "org.hatchet-player.Player.InfoPlugin" )
    Q_OBJECT
    Q_INTERFACES( Hatchet::InfoSystem::InfoPlugin )

public:
    RoviPlugin();
    virtual ~RoviPlugin();

protected:
    virtual void init() {}
    
    virtual void notInCacheSlot( Hatchet::InfoSystem::InfoStringHash criteria, Hatchet::InfoSystem::InfoRequestData requestData );

    virtual void pushInfo( Hatchet::InfoSystem::InfoPushData pushData )
    {
        Q_UNUSED( pushData );
    }

    virtual void getInfo( Hatchet::InfoSystem::InfoRequestData requestData );

private slots:
    void albumLookupFinished();
    void albumLookupError( QNetworkReply::NetworkError );
private:
    QNetworkReply* makeRequest( QUrl url );
    QByteArray generateSig() const;

    QByteArray m_apiKey;
    QByteArray m_secret;
};

}

}

#endif // ROVIPLUGIN_H
