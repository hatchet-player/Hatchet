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

#ifndef HATCHET_INFOSYSTEMCACHE_H
#define HATCHET_INFOSYSTEMCACHE_H

#include <QCache>
#include <QDateTime>
#include <QObject>
#include <QtDebug>
#include <QTimer>

#include "InfoSystem.h"

namespace Hatchet
{

namespace InfoSystem
{

class DLLEXPORT InfoSystemCache : public QObject
{
Q_OBJECT

public:
    InfoSystemCache( QObject *parent = 0 );

    virtual ~InfoSystemCache();

signals:
    void info( Hatchet::InfoSystem::InfoRequestData requestData, QVariant output );

public slots:
    void getCachedInfoSlot( Hatchet::InfoSystem::InfoStringHash criteria, qint64 newMaxAge, Hatchet::InfoSystem::InfoRequestData requestData );
    void updateCacheSlot( Hatchet::InfoSystem::InfoStringHash criteria, qint64 maxAge, Hatchet::InfoSystem::InfoType type, QVariant output );

private slots:
    void pruneTimerFired();

private:
    /**
     * Version number of the infosystem cache.
     * If you change existing cached data,
     * increase this number.
     */
    static const int s_infosystemCacheVersion;

    void notInCache( QObject *receiver, Hatchet::InfoSystem::InfoStringHash criteria, Hatchet::InfoSystem::InfoRequestData requestData );
    const QString criteriaMd5( const Hatchet::InfoSystem::InfoStringHash &criteria, Hatchet::InfoSystem::InfoType type = Hatchet::InfoSystem::InfoNoInfo ) const;

    QString m_cacheBaseDir;
    QHash< InfoType, QHash< QString, QString > > m_fileLocationCache;
    QTimer m_pruneTimer;
    QCache< QString, QVariant > m_dataCache;
};

} //namespace InfoSystem

} //namespace Hatchet

Q_DECLARE_METATYPE( Hatchet::InfoSystem::InfoSystemCache* )

#endif //HATCHET_INFOSYSTEMCACHE_H
