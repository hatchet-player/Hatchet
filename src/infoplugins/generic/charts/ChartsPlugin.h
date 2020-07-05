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

#ifndef ChartsPlugin_H
#define ChartsPlugin_H

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

class INFOPLUGINDLLEXPORT ChartsPlugin : public InfoPlugin
{
    Q_PLUGIN_METADATA( IID "org.hatchet-player.Player.InfoPlugin" )
    Q_OBJECT
    Q_INTERFACES( Hatchet::InfoSystem::InfoPlugin )

public:
    ChartsPlugin();
    virtual ~ChartsPlugin();

    enum ChartType {
        None =      0x00,
        Track =     0x01,
        Album =     0x02,
        Artist =    0x04
    };

    void setChartType( ChartType type ) { m_chartType = type; }
    ChartType chartType() const { return m_chartType; }

protected slots:
    virtual void init();
    virtual void getInfo( Hatchet::InfoSystem::InfoRequestData requestData );
    virtual void notInCacheSlot( Hatchet::InfoSystem::InfoStringHash criteria, Hatchet::InfoSystem::InfoRequestData requestData );

    virtual void pushInfo( Hatchet::InfoSystem::InfoPushData pushData )
    {
        Q_UNUSED( pushData );
    }

    /**
     * Parses a QNetworkReply of a list of chart sources.
     */
    void chartSourcesList();

    /**
     * Parses a QNetworkReply of a list of charts for a particular source
     */
    void chartsList();

    /**
     * Parses a QNetworkReply for the chart data for a particular chart
     */
    void chartReturned();

private:
    /**
     * Fetch list of chart sources (e.g., itunes, billboard)
     * Populates the m_chartResources member.
     */
    void fetchChartSourcesList( bool fetchOnlySourceList );
    /**
     * Requests charts list for each chart source in m_chartResources
     */
    void fetchAllChartSources();
    /**
     * Fetches a specific chart from a particular source.
     * Updates the cache.
     */
    void fetchChart( Hatchet::InfoSystem::InfoRequestData requestData, const QString& source, const QString& chart_id );
    void fetchSource( const QString& source );
    void fetchChartFromCache( Hatchet::InfoSystem::InfoRequestData requestData );
    void fetchExpiredSources();

    void fetchChartCapabilitiesFromCache( Hatchet::InfoSystem::InfoRequestData requestData );
    void dataError( Hatchet::InfoSystem::InfoRequestData requestData );

    QString countryName( const QString& cc );

    qlonglong getMaxAge( const QByteArray &rawHeader ) const;
    qlonglong getMaxAge( const qlonglong expires ) const;

    QVariantMap m_allChartsMap;
    QHash< QString, QString > m_cachedCountries;
    QList< Hatchet::InfoSystem::InfoStringHash > m_chartResources;
    QList< InfoRequestData > m_cachedRequests;
    QStringList m_refetchSource;
    QString m_cacheIdentifier;
    QString m_chartVersion;
    ChartType m_chartType;

    uint m_chartsFetchJobs;
    bool m_fetchAll;

};

}

}

#endif // ChartsPlugin_H
