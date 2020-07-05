/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2015, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include "MusicBrainzPlugin.h"

#include "utils/HatchetUtils.h"
#include "utils/Logger.h"
#include "utils/NetworkAccessManager.h"
#include "HatchetVersion.h"

#include <QNetworkReply>
#include <QDomDocument>

using namespace Hatchet::InfoSystem;


MusicBrainzPlugin::MusicBrainzPlugin()
    : InfoPlugin()
{
    qDebug() << Q_FUNC_INFO;
    m_supportedGetTypes << Hatchet::InfoSystem::InfoArtistReleases << Hatchet::InfoSystem::InfoAlbumSongs;
}


MusicBrainzPlugin::~MusicBrainzPlugin()
{
    qDebug() << Q_FUNC_INFO;
}


void
MusicBrainzPlugin::getInfo( Hatchet::InfoSystem::InfoRequestData requestData )
{
    if ( !requestData.input.canConvert< Hatchet::InfoSystem::InfoStringHash >() )
    {
        emit info( requestData, QVariant() );
        return;
    }
    InfoStringHash hash = requestData.input.value< Hatchet::InfoSystem::InfoStringHash >();
    if ( !hash.contains( "artist" ) )
    {
        emit info( requestData, QVariant() );
        return;
    }

    switch ( requestData.type )
    {
        case InfoArtistReleases:
        {
            Hatchet::InfoSystem::InfoStringHash criteria;
            criteria["artist"] = hash["artist"];

            emit getCachedInfo( criteria, Q_INT64_C(2419200000), requestData );
            break;
        }

        case InfoAlbumSongs:
        {
            Hatchet::InfoSystem::InfoStringHash criteria;
            criteria["artist"] = hash["artist"];
            criteria["album"] = hash["album"];

            emit getCachedInfo( criteria, Q_INT64_C(2419200000), requestData );

            break;
        }

        default:
        {
            Q_ASSERT( false );
            break;
        }
    }
}

QNetworkReply*
MusicBrainzPlugin::getUrl(QUrl url, QVariant requestData)
{
    QNetworkRequest request =  QNetworkRequest( url );
    QByteArray userAgent = HatchetUtils::userAgentString( HATCHET_APPLICATION_NAME, HATCHET_VERSION ).toUtf8();
    request.setRawHeader( "User-Agent", userAgent );
    QNetworkReply* reply = Hatchet::Utils::nam()->get( request );
    reply->setProperty( "requestData", requestData );
    return reply;
}

void
MusicBrainzPlugin::notInCacheSlot( InfoStringHash criteria, InfoRequestData requestData )
{
    QString querySt;
    switch ( requestData.type )
    {
        case InfoArtistReleases:
        {
            querySt.append( QString( "artist:\"%1\"" ).arg(criteria["artist"]) );
            querySt.append( " AND (type:album OR type:ep OR type:remix)" );
            querySt.append( " AND status:official" );
            querySt.append( " AND NOT secondarytype:live" );
            querySt.append( " AND NOT secondarytype:compilation" );
            // we dont handle more than 100 results atm, but not even the beatles have more than 100 ep+albums, so its probably safe

            QString requestString( "http://musicbrainz.org/ws/2/release-group" );
            QUrl url( requestString );

            HatchetUtils::urlAddQueryItem( url, "query", querySt );
            HatchetUtils::urlAddQueryItem( url, "limit", "100" );

            tDebug() << Q_FUNC_INFO << url.toString();
            QNetworkReply* reply = getUrl( url, QVariant::fromValue< Hatchet::InfoSystem::InfoRequestData >( requestData ) );

            connect( reply, SIGNAL( finished() ), SLOT( gotReleaseGroupsSlot() ) );

            break;
        }
        case InfoAlbumSongs:
        {
            querySt.append( QString( "release:\"%1\"" ).arg(criteria["album"]) );
            querySt.append( QString( " AND artist:\"%1\"" ).arg(criteria["artist"]) );
            // not pre-filtering will yield more than 100 results which we dont handle atm. But since we only take the first result anyway that wont hurt

            QString requestString( "http://musicbrainz.org/ws/2/release" );
            QUrl url( requestString );

            HatchetUtils::urlAddQueryItem( url, "query", querySt );
            HatchetUtils::urlAddQueryItem( url, "limit", "100" );

            tDebug() << Q_FUNC_INFO << url.toString();
            QNetworkReply* reply = getUrl( url, QVariant::fromValue< Hatchet::InfoSystem::InfoRequestData >( requestData ) );

            connect( reply, SIGNAL( finished() ), SLOT( gotReleasesSlot() ) );

            break;
        }
        default:
        {
            Q_ASSERT( false );
            break;
        }
    }
}


void
MusicBrainzPlugin::gotReleaseGroupsSlot()
{
    QNetworkReply* oldReply = qobject_cast<QNetworkReply*>( sender() );
    if ( !oldReply )
        return; //timeout will handle it
    oldReply->deleteLater();
    tDebug() << Q_FUNC_INFO << "HTTP response code:" << oldReply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt();

    QDomDocument doc;
    doc.setContent( oldReply->readAll() );
    QDomNodeList releaseGroupsNL = doc.elementsByTagName( "release-group" );
    if ( releaseGroupsNL.isEmpty() )
    {
        emit info( oldReply->property( "requestData" ).value< Hatchet::InfoSystem::InfoRequestData >(), QVariant() );
        tDebug() << Q_FUNC_INFO << doc.toString();
        return;
    }

    Hatchet::InfoSystem::InfoRequestData requestData = oldReply->property( "requestData" ).value< Hatchet::InfoSystem::InfoRequestData >();
    InfoStringHash hash = requestData.input.value< Hatchet::InfoSystem::InfoStringHash >();
    switch ( requestData.type )
    {
        case InfoArtistReleases:
        {
            QString popularId = releaseGroupsNL.at(0).firstChildElement( "artist-credit" ).firstChildElement( "name-credit" ).firstChildElement( "artist" ).attribute( "id" );

            QStringList albums;
            for ( int i = 0; i < releaseGroupsNL.count(); i++ )
            {
                QString groupTitle = releaseGroupsNL.at(i).firstChildElement("title").text();
                QString a = releaseGroupsNL.at(i).firstChildElement( "artist-credit" ).firstChildElement( "name-credit" ).firstChildElement( "artist" ).firstChildElement( "name" ).text();
                QString id = releaseGroupsNL.at(i).firstChildElement( "artist-credit" ).firstChildElement( "name-credit" ).firstChildElement( "artist" ).attribute( "id" );
                if ( !albums.contains( groupTitle ) && id == popularId && a.normalized( QString::NormalizationForm_KC ).compare(hash["artist"].normalized( QString::NormalizationForm_KC ), Qt::CaseInsensitive) == 0 )
                {
                    albums << groupTitle;
                    tDebug() << Q_FUNC_INFO << groupTitle;
                }
            }

            QVariantMap returnedData;
            returnedData["albums"] = albums;
            emit info( requestData, returnedData );

            Hatchet::InfoSystem::InfoStringHash origData = requestData.input.value< Hatchet::InfoSystem::InfoStringHash>();
            Hatchet::InfoSystem::InfoStringHash criteria;
            criteria["artist"] = origData["artist"];
            emit updateCache( criteria, Q_INT64_C(0), requestData.type, returnedData );
            break;
        }

        default:
        {
            Q_ASSERT( false );
            break;
        }
    }
}


void
MusicBrainzPlugin::gotReleasesSlot()
{
    QNetworkReply* oldReply = qobject_cast<QNetworkReply*>( sender() );
    if ( !oldReply )
        return; //timeout will handle it
    oldReply->deleteLater();

    QDomDocument doc;
    doc.setContent( oldReply->readAll() );
    QDomNodeList releasesNL = doc.elementsByTagName( "release" );
    if ( releasesNL.isEmpty() )
    {
        emit info( oldReply->property( "requestData" ).value< Hatchet::InfoSystem::InfoRequestData >(), QVariant() );
        tDebug() << Q_FUNC_INFO << doc.toString();
        return;
    }

    Hatchet::InfoSystem::InfoRequestData requestData = oldReply->property( "requestData" ).value< Hatchet::InfoSystem::InfoRequestData >();
    switch ( requestData.type )
    {
        case InfoAlbumSongs:
        {
            // we can simply use the first result as they are sorted by score
            QString release_id = releasesNL.at(0).toElement().attribute( "id" );

            QString requestString = QString( "http://musicbrainz.org/ws/2/release/%1" ).arg( release_id );
            QUrl url( requestString );
            HatchetUtils::urlAddQueryItem( url, "inc", "recordings" );
            tDebug() << Q_FUNC_INFO << url.toString();

            QNetworkReply* newReply = getUrl( url, oldReply->property( "requestData" ) );
            connect( newReply, SIGNAL( finished() ), SLOT( gotRecordingsSlot() ) );

            break;
        }

        default:
        {
            Q_ASSERT( false );
            break;
        }
    }
}


void
MusicBrainzPlugin::gotRecordingsSlot()
{
    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    if ( !reply )
        return; //timeout will handle it
    reply->deleteLater();

    tDebug() << Q_FUNC_INFO << "HTTP response code:" << reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt();

    QDomDocument doc;
    doc.setContent( reply->readAll() );
    QDomNodeList mediumList = doc.elementsByTagName( "medium-list" );
    if ( mediumList.isEmpty() )
    {
        emit info( reply->property( "requestData" ).value< Hatchet::InfoSystem::InfoRequestData >(), QVariant() );
        tDebug() << Q_FUNC_INFO << doc.toString();
        return;
    }

    QDomNodeList tracksNL = mediumList.at(0).toElement().elementsByTagName( "track" );
    QStringList tracksSL;
    for ( int i = 0; i < tracksNL.count(); i++ )
    {
        QString track = tracksNL.at(i).firstChildElement( "recording" ).firstChildElement( "title" ).text();
        if ( !tracksSL.contains( track ) )
        {
            tracksSL << track;
            tDebug(LOGVERBOSE) << Q_FUNC_INFO << track;
        }
    }

    Hatchet::InfoSystem::InfoRequestData requestData = reply->property( "requestData" ).value< Hatchet::InfoSystem::InfoRequestData >();
    QVariantMap returnedData;
    returnedData["tracks"] = tracksSL;
    emit info( requestData, returnedData );

    Hatchet::InfoSystem::InfoStringHash origData = requestData.input.value< Hatchet::InfoSystem::InfoStringHash>();
    Hatchet::InfoSystem::InfoStringHash criteria;
    criteria["artist"] = origData["artist"];
    criteria["album"] = origData["album"];
    emit updateCache( criteria, Q_INT64_C(0), requestData.type, returnedData );
}

Q_EXPORT_PLUGIN2( Hatchet::InfoSystem::InfoPlugin, Hatchet::InfoSystem::MusicBrainzPlugin )

