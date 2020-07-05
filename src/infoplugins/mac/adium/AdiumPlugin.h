/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
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

#ifndef ADIUMPLUGIN_H
#define ADIUMPLUGIN_H

#include "../../InfoPluginDllMacro.h"

#include "infosystem/InfoSystem.h"

#include <QNetworkAccessManager>
#include <QObject>
#include <QVariant>
#include <QPointer>

class QTimer;

namespace Hatchet {

namespace InfoSystem {

class INFOPLUGINDLLEXPORT AdiumPlugin : public InfoPlugin
{
    Q_PLUGIN_METADATA( IID "org.hatchet-player.Player.InfoPlugin" )
    Q_OBJECT
    Q_INTERFACES( Hatchet::InfoSystem::InfoPlugin )

public:
    AdiumPlugin();
    virtual ~AdiumPlugin();

protected slots:
    virtual void init() {}
    
    virtual void getInfo( Hatchet::InfoSystem::InfoRequestData requestData )
    {
        Q_UNUSED( requestData );
    }

    virtual void pushInfo( Hatchet::InfoSystem::InfoPushData pushData );

public slots:
    virtual void notInCacheSlot( const Hatchet::InfoSystem::InfoStringHash criteria, Hatchet::InfoSystem::InfoRequestData requestData )
    {
        Q_UNUSED( criteria );
        Q_UNUSED( requestData );
    }

private slots:
    void clearStatus();
    void settingsChanged();
    void onQueryLinkReady( const QVariantMap& data );

private:
    void audioStarted( const Hatchet::InfoSystem::PushInfoPair pushInfoPair );
    void audioFinished( const QVariant &input );
    void audioStopped();
    void audioPaused();
    void audioResumed( const Hatchet::InfoSystem::PushInfoPair pushInfoPair );

    bool m_active;
    QString m_beforeStatus;
    QString m_afterStatus;

    QString m_currentTitle;
    QString m_currentArtist;
    QUrl m_currentLongUrl;

    QTimer* m_pauseTimer;
    QPointer<QNetworkAccessManager> m_nam;

};


}

}

#endif // ADIUMPLUGIN_H
