/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Hugo Lindström <hugolm84@gmail.com>
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

#ifndef HYPEMPLUGIN_H
#define HYPEMPLUGIN_H

#include "../../InfoPluginDllMacro.h"

#include "infosystem/InfoSystem.h"
#include "infosystem/InfoSystemWorker.h"
#include <QNetworkReply>
#include <QObject>

class QNetworkReply;

namespace Hatchet
{

namespace InfoSystem
{

class INFOPLUGINDLLEXPORT HypemPlugin : public InfoPlugin
{
    Q_PLUGIN_METADATA( IID "org.hatchet-player.Player.InfoPlugin" )
    Q_OBJECT
    Q_INTERFACES( Hatchet::InfoSystem::InfoPlugin )

public:
    HypemPlugin();
    virtual ~HypemPlugin();

    enum ChartType {
        None =      0x00,
        Track =     0x01,
        Album =     0x02,
        Artist =    0x04

    };
    void setChartType( ChartType type ) { m_chartType = type; }
    ChartType chartType() const { return m_chartType; }

public slots:
    void chartReturned();
    void chartTypes();

protected slots:
    virtual void init();
    virtual void getInfo( Hatchet::InfoSystem::InfoRequestData requestData );
    virtual void notInCacheSlot( Hatchet::InfoSystem::InfoStringHash criteria, Hatchet::InfoSystem::InfoRequestData requestData );
    virtual void pushInfo( Hatchet::InfoSystem::InfoPushData pushData )
    {
        Q_UNUSED( pushData );
    }


private:
    void fetchChart( Hatchet::InfoSystem::InfoRequestData requestData );
    void fetchChartCapabilities( Hatchet::InfoSystem::InfoRequestData requestData );
    void dataError( Hatchet::InfoSystem::InfoRequestData requestData );

    QVariantList m_chartResources;
    QList<InfoStringHash> m_charts;


    ChartType m_chartType;
    QVariantMap m_allChartsMap;
    QVariantList m_types;
    QVariantList m_popularTypes;
    QVariantList m_trackTypes;
    QVariantList m_byTagTypes;


    uint m_chartsFetchJobs;
    QList< InfoRequestData > m_cachedRequests;

    QHash< QString, QString > m_cachedCountries;
};

}

}

#endif // HYPEMPLUGIN_H
