/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Hugo Lindström <hugolm84@gmail.com>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2015, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include "HypemPlugin.h"

#include <QDir>
#include <QSettings>
#include <QCryptographicHash>
#include <QNetworkConfiguration>
#include <QNetworkReply>

#include "Album.h"
#include "Typedefs.h"
#include "HatchetSettings.h"
#include "utils/HatchetUtils.h"
#include "infosystem/InfoSystemWorker.h"
#include "utils/Json.h"
#include "utils/Logger.h"
#include "utils/NetworkAccessManager.h"
#include "Source.h"

#define HYPEM_URL "http://hypem.com/playlist/"
#define HYPEM_END_URL "json/1/data.js"

namespace Hatchet
{

namespace InfoSystem
{


HypemPlugin::HypemPlugin()
    : InfoPlugin()
    , m_chartsFetchJobs( 0 )
{

    m_supportedGetTypes << InfoChart << InfoChartCapabilities;
    m_types << "Artists" << "Tracks" << "Recent by Tag";

    m_trackTypes    << "Last 3 Days"
                    << "Last Week"
                    << "No Remixes"
                    << "On Twitter";

    m_byTagTypes    << "Dance"
                    << "Experimental"
                    << "Electronic"
                    << "Funk"
                    << "Hip-hop"
                    << "Indie"
                    << "Instrumental"
                    << "Post-punk"
                    << "Rock"
                    << "Singer-songwriter"
                    << "Alternative"
                    << "Pop"
                    << "Female"
                    << "Vocalist"
                    << "Folk"
                    << "Electro"
                    << "Lo-fi"
                    << "Psychedelic"
                    << "Rap"
                    << "British"
                    << "Ambient"
                    << "Dubstep"
                    << "House"
                    << "Chillwave"
                    << "Dreampop"
                    << "Shoegaze"
                    << "Chillout"
                    << "Soul"
                    << "French"
                    << "Acoustic"
                    << "Canadian"
                    << "60s"
                    << "80s"
                    << "Techno"
                    << "Punk"
                    << "New wave";
}


HypemPlugin::~HypemPlugin()
{
    tDebug() << Q_FUNC_INFO;
}


void
HypemPlugin::init()
{
    chartTypes();
}


void
HypemPlugin::dataError( Hatchet::InfoSystem::InfoRequestData requestData )
{
    emit info( requestData, QVariant() );
    return;
}


void
HypemPlugin::getInfo( Hatchet::InfoSystem::InfoRequestData requestData )
{
    qDebug() << Q_FUNC_INFO << requestData.caller;
    qDebug() << Q_FUNC_INFO << requestData.customData;

    InfoStringHash hash = requestData.input.value< Hatchet::InfoSystem::InfoStringHash >();
    switch ( requestData.type )
    {
        case InfoChart:
            if ( !hash.contains( "chart_source" ) || hash["chart_source"].toLower() != "hype machine" )
            {
                dataError( requestData );
                break;
            }
            qDebug() << Q_FUNC_INFO << "InfoCHart req for" << hash["chart_source"];
            fetchChart( requestData );
            break;

        case InfoChartCapabilities:
            fetchChartCapabilities( requestData );
            break;

        default:
            dataError( requestData );
    }
}


void
HypemPlugin::fetchChart( Hatchet::InfoSystem::InfoRequestData requestData )
{
    if ( !requestData.input.canConvert< Hatchet::InfoSystem::InfoStringHash >() )
    {
        dataError( requestData );
        return;
    }

    InfoStringHash hash = requestData.input.value< Hatchet::InfoSystem::InfoStringHash >();
    Hatchet::InfoSystem::InfoStringHash criteria;

    /// Each request needs to contain both a id and source
    if ( !hash.contains( "chart_id" ) && !hash.contains( "chart_source" ) )
    {
        dataError( requestData );
        return;

    }
    /// Set the criterias for current chart
    criteria["chart_id"] = hash["chart_id"];
    criteria["chart_source"] = hash["chart_source"];
    /// @todo
    /// set cache time based on wether requested type is 3day, lastweek or recent.
    emit getCachedInfo( criteria, Q_INT64_C(86400000), requestData );
}


void
HypemPlugin::fetchChartCapabilities( Hatchet::InfoSystem::InfoRequestData requestData )
{
    if ( !requestData.input.canConvert< Hatchet::InfoSystem::InfoStringHash >() )
    {
        dataError( requestData );
        return;
    }

    Hatchet::InfoSystem::InfoStringHash criteria;
    emit getCachedInfo( criteria, Q_INT64_C(0), requestData );
}


void
HypemPlugin::notInCacheSlot( QHash<QString, QString> criteria, Hatchet::InfoSystem::InfoRequestData requestData )
{
    tDebug( LOGVERBOSE ) << "HypemPlugin thread: " << QThread::currentThread() << ", InfoSystemWorker thread: " << Hatchet::InfoSystem::InfoSystem::instance()->workerThread().data()->currentThread();
    switch ( requestData.type )
    {
        case InfoChart:
        {
            /// Fetch the chart, we need source and id
            tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "InfoChart not in cache! Fetching...";
            QUrl url = QUrl( QString( HYPEM_URL "%1/%2" ).arg( criteria["chart_id"].toLower() ).arg(HYPEM_END_URL) );
            qDebug() << Q_FUNC_INFO << "Getting chart url" << url;

            QNetworkReply* reply = Hatchet::Utils::nam()->get( QNetworkRequest( url ) );
            reply->setProperty( "requestData", QVariant::fromValue< Hatchet::InfoSystem::InfoRequestData >( requestData ) );
            connect( reply, SIGNAL( finished() ), SLOT( chartReturned() ) );
            return;
        }

        case InfoChartCapabilities:
        {
            tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "InfoChartCapabilities not in cache! Fetching...";
            if ( m_chartsFetchJobs > 0 )
            {
                qDebug() << Q_FUNC_INFO << "InfoChartCapabilities still fetching!";
                m_cachedRequests.append( requestData );
                return;
            }

            emit info( requestData, m_allChartsMap );
            return;
        }

        default:
        {
            tLog() << Q_FUNC_INFO << "Couldn't figure out what to do with this type of request after cache miss";
            emit info( requestData, QVariant() );
            return;
        }
    }
}


void
HypemPlugin::chartTypes()
{
    /// Get possible chart type for specificHypemPlugin: InfoChart types returned chart source
    tDebug() << Q_FUNC_INFO << "Got hypem types";

    QVariantMap charts;
    foreach ( const QVariant& types, m_types )
    {
        QList< InfoStringHash > chart_types;
        QList< InfoStringHash > pop_charts;
        InfoStringHash c;

        if ( types.toString() != "Artists" )
        {
            if ( types.toString() == "Tracks" )
            {
                foreach ( const QVariant& trackType, m_trackTypes )
                {
                    QString typeId;
                    if ( trackType.toString() == "Last 3 Days" )
                        typeId = "popular/3day";

                    if ( trackType.toString() == "Last Week" )
                        typeId = "popular/lastweek";

                    if ( trackType.toString() == "No Remixes" )
                        typeId = "popular/noremix";

                    if ( trackType.toString() == "On Twitter" )
                        typeId = "popular/twitter";

                    c[ "id" ] = typeId;
                    c[ "label" ] = trackType.toString();
                    c[ "type" ] = "tracks";
                    pop_charts.append( c );
                }

                chart_types.append( pop_charts );
            }
            else if ( types.toString() == "Recent by Tag" )
            {
                foreach ( const QVariant& tagTypes, m_byTagTypes )
                {
                    c[ "id" ] = "tags/" + tagTypes.toString().toLower();
                    c[ "label" ] = tagTypes.toString();
                    c[ "type" ] = tagTypes.toString();
                    chart_types.append( c );
                }
            }
        }
        else
        {
            InfoStringHash c;
            c[ "id" ] = "popular/artists";
            c[ "label" ] = "Most Recent";
            c[ "type" ] = "artists";
            chart_types.append( c );
        }

        charts.insert( types.toString(), QVariant::fromValue<QList< InfoStringHash > >( chart_types ) );
    }

    m_allChartsMap.insert( "Hype Machine", QVariant::fromValue<QVariantMap>( charts ) );
    qDebug() << "HypemPlugin:Chartstype: " << m_allChartsMap;
}


void
HypemPlugin::chartReturned()
{
    /// Chart request returned something! Woho
    QNetworkReply* reply = qobject_cast<QNetworkReply*>( sender() );
    reply->deleteLater();

    QString url = reply->url().toString();
    QVariantMap returnedData;
    if ( reply->error() == QNetworkReply::NoError )
    {
        bool ok;
        QByteArray jsonData = reply->readAll();
        QVariantMap res = HatchetUtils::parseJson( jsonData, &ok ).toMap();

        if ( !ok )
        {
            tLog() << "Failed to parse json from chart lookup:" << jsonData;
            return;
        }

        /// SO we have a result, parse it!
        QList< InfoStringHash > top_tracks;
        QStringList top_artists;

        if ( url.contains( "artists" ) )
            setChartType( Artist );
        else
            setChartType( Track );

        foreach ( QVariant result, res )
        {
            QString title, artist;
            QVariantMap chartMap = result.toMap();

            if ( !chartMap.isEmpty() )
            {

                title = chartMap.value( "title" ).toString();
                artist = chartMap.value( "artist" ).toString();

                if ( chartType() == Track )
                {
                    InfoStringHash pair;
                    pair["artist"] = artist;
                    pair["track"] = title;
                    top_tracks << pair;
                }

                if ( chartType() == Artist )
                    top_artists << artist;
            }
        }

        if ( chartType() == Track )
        {
            tDebug() << "HypemPlugin:" << "\tgot " << top_tracks.size() << " tracks";
            returnedData["tracks"] = QVariant::fromValue( top_tracks );
            returnedData["type"] = "tracks";
        }

        if ( chartType() == Artist )
        {
            tDebug() << "HypemPlugin:" << "\tgot " << top_artists.size() << " artists";
            returnedData["artists"] = top_artists;
            returnedData["type"] = "artists";
        }

        Hatchet::InfoSystem::InfoRequestData requestData = reply->property( "requestData" ).value< Hatchet::InfoSystem::InfoRequestData >();
        emit info( requestData, returnedData );

        // update cache
        Hatchet::InfoSystem::InfoStringHash criteria;
        Hatchet::InfoSystem::InfoStringHash origData = requestData.input.value< Hatchet::InfoSystem::InfoStringHash >();
        criteria[ "chart_id" ] = origData[ "chart_id" ];
        criteria[ "chart_source" ] = origData[ "chart_source" ];
        /// @todo
        /// set cache time based on wether requested type is 3day, lastweek or recent.
        emit updateCache( criteria, Q_INT64_C(86400000), requestData.type, returnedData );
    }
    else
        qDebug() << "Network error in fetching chart:" << reply->url().toString();
}

}

}

Q_EXPORT_PLUGIN2( Hatchet::InfoSystem::InfoPlugin, Hatchet::InfoSystem::HypemPlugin )
