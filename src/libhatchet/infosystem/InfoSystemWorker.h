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

#ifndef HATCHET_INFOSYSTEMWORKER_H
#define HATCHET_INFOSYSTEMWORKER_H

#include "infosystem/InfoSystem.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QObject>
#include <QtCore/QtDebug>
#include <QtCore/QMap>
#include <QtCore/QSet>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QTimer>

#include "DllMacro.h"

namespace Hatchet {

namespace InfoSystem {

class InfoSystemCache;


class DLLEXPORT InfoSystemWorker : public QObject
{
    Q_OBJECT

public:
    InfoSystemWorker();
    ~InfoSystemWorker();

    const QList< InfoPluginPtr > plugins() const;

signals:
    void info( Hatchet::InfoSystem::InfoRequestData requestData, QVariant output );
    void finished( QString target );
    void finished( QString target, Hatchet::InfoSystem::InfoType type );

    void updatedSupportedGetTypes( Hatchet::InfoSystem::InfoTypeSet supportedTypes );
    void updatedSupportedPushTypes( Hatchet::InfoSystem::InfoTypeSet supportedTypes );

public slots:
    void init( Hatchet::InfoSystem::InfoSystemCache* cache );
    void getInfo( Hatchet::InfoSystem::InfoRequestData requestData );

    void pushInfo( Hatchet::InfoSystem::InfoPushData pushData );
    
    void infoSlot( Hatchet::InfoSystem::InfoRequestData requestData, QVariant output );

    void addInfoPlugin( Hatchet::InfoSystem::InfoPluginPtr plugin );
    void removeInfoPlugin( Hatchet::InfoSystem::InfoPluginPtr plugin );
    void loadInfoPlugins();

private slots:
    void checkTimeoutsTimerFired();

private:
    void registerInfoTypes( const InfoPluginPtr &plugin, const QSet< InfoType > &getTypes, const QSet< InfoType > &pushTypes );
    void deregisterInfoTypes( const InfoPluginPtr &plugin, const QSet< InfoType > &getTypes, const QSet< InfoType > &pushTypes );

    void checkFinished( const Hatchet::InfoSystem::InfoRequestData &target );
    QList< InfoPluginPtr > determineOrderedMatches( const InfoType type ) const;

    QHash< QString, QHash< InfoType, int > > m_dataTracker;
    QMultiMap< qint64, quint64 > m_timeRequestMapper;
    QHash< uint, bool > m_requestSatisfiedMap;
    QHash< uint, InfoRequestData* > m_savedRequestMap;

    // NOTE Cache object lives in a different thread, do not call methods on it directly
    InfoSystemCache* m_cache;

    // For now, statically instantiate plugins; this is just somewhere to keep them
    QList< InfoPluginPtr > m_plugins;

    QMap< InfoType, QList< InfoPluginPtr > > m_infoGetMap;
    QMap< InfoType, QList< InfoPluginPtr > > m_infoPushMap;

    QTimer m_checkTimeoutsTimer;

    quint64 m_shortLinksWaiting;
};

}

}

#endif // HATCHET_INFOSYSTEMWORKER_H
