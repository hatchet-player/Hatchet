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

#include "MusixMatchPlugin.h"

#include "utils/HatchetUtils.h"
#include "utils/Logger.h"
#include "utils/NetworkAccessManager.h"

#include <QNetworkReply>
#include <QDomDocument>

using namespace Hatchet::InfoSystem;


// for internal neatness

MusixMatchPlugin::MusixMatchPlugin()
    : InfoPlugin()
    , m_apiKey( "61be4ea5aea7dd942d52b2f1311dd9fe" )
{
    tDebug() << Q_FUNC_INFO;
    m_supportedGetTypes << Hatchet::InfoSystem::InfoTrackLyrics;
}


MusixMatchPlugin::~MusixMatchPlugin()
{
    qDebug() << Q_FUNC_INFO;
}


void
MusixMatchPlugin::getInfo( Hatchet::InfoSystem::InfoRequestData requestData )
{
    tDebug() << Q_FUNC_INFO;
    if( !isValidTrackData( requestData ) || requestData.type != Hatchet::InfoSystem::InfoTrackLyrics )
        return;
    InfoStringHash hash = requestData.input.value< Hatchet::InfoSystem::InfoStringHash >();

    QString artist = hash["artist"];
    QString track = hash["track"];
    if( artist.isEmpty() || track.isEmpty() )
    {
        emit info( requestData, QVariant() );
        return;
    }
    tDebug() << "artist is " << artist << ", track is " << track;
    QString requestString( "http://api.musixmatch.com/ws/1.1/track.search?format=xml&page_size=1&f_has_lyrics=1" );
    QUrl url( requestString );

    HatchetUtils::urlAddQueryItem( url, "apikey", m_apiKey );
    HatchetUtils::urlAddQueryItem( url, "q_artist", artist );
    HatchetUtils::urlAddQueryItem( url, "q_track", track );

    QNetworkReply* reply = Hatchet::Utils::nam()->get( QNetworkRequest( url ) );
    reply->setProperty( "requestData", QVariant::fromValue< Hatchet::InfoSystem::InfoRequestData >( requestData ) );

    connect( reply, SIGNAL( finished() ), SLOT( trackSearchSlot() ) );
}


bool
MusixMatchPlugin::isValidTrackData( Hatchet::InfoSystem::InfoRequestData requestData )
{
    tDebug() << Q_FUNC_INFO;

    if ( !requestData.input.canConvert< Hatchet::InfoSystem::InfoStringHash >() )
    {
        emit info( requestData, QVariant() );
        tDebug() << "MusixMatchPlugin::isValidTrackData: Data null, invalid, or can't convert" << requestData.input.isNull() << requestData.input.isValid() << requestData.input.canConvert< QVariantMap >();
        return false;
    }
    InfoStringHash hash = requestData.input.value< Hatchet::InfoSystem::InfoStringHash >();

    if ( hash[ "track" ].isEmpty() )
    {
        emit info( requestData, QVariant() );
        tDebug() << "MusixMatchPlugin::isValidTrackData: Track name is empty";
        return false;
    }
    if ( hash[ "artist" ].isEmpty() )
    {
        emit info( requestData, QVariant() );
        tDebug() << "MusixMatchPlugin::isValidTrackData: No artist name found";
        return false;
    }
    return true;
}


void
MusixMatchPlugin::trackSearchSlot()
{
    tDebug() << Q_FUNC_INFO;
    QNetworkReply* oldReply = qobject_cast<QNetworkReply*>( sender() );
    if ( !oldReply )
        return; //timeout will handle it
    oldReply->deleteLater();

    QDomDocument doc;
    doc.setContent(oldReply->readAll());
    qDebug() << Q_FUNC_INFO << doc.toString();
    QDomNodeList domNodeList = doc.elementsByTagName("track_id");
    if ( domNodeList.isEmpty() )
    {
        emit info( oldReply->property( "requestData" ).value< Hatchet::InfoSystem::InfoRequestData >(), QVariant() );
        return;
    }
    QString track_id = domNodeList.at(0).toElement().text();
    QString requestString( "http://api.musixmatch.com/ws/1.1/track.lyrics.get?track_id=%1&format=xml&apikey=%2" );
    QUrl url( requestString );

    HatchetUtils::urlAddQueryItem( url, "apikey", m_apiKey );
    HatchetUtils::urlAddQueryItem( url, "track_id", track_id );

    QNetworkReply* newReply = Hatchet::Utils::nam()->get( QNetworkRequest( url ) );
    newReply->setProperty( "requestData", oldReply->property( "requestData" ) );
    connect( newReply, SIGNAL( finished() ), SLOT( trackLyricsSlot() ) );
}


void
MusixMatchPlugin::trackLyricsSlot()
{
    tDebug() << Q_FUNC_INFO;
    QNetworkReply* reply = qobject_cast< QNetworkReply* >( sender() );
    if ( !reply )
        return; //timeout will handle it
    reply->deleteLater();

    QDomDocument doc;
    doc.setContent( reply->readAll() );
    QDomNodeList domNodeList = doc.elementsByTagName( "lyrics_body" );
    if ( domNodeList.isEmpty() )
    {
        emit info( reply->property( "requestData" ).value< Hatchet::InfoSystem::InfoRequestData >(), QVariant() );
        return;
    }
    QString lyrics = domNodeList.at(0).toElement().text();
    emit info( reply->property( "requestData" ).value< Hatchet::InfoSystem::InfoRequestData >(), QVariant( lyrics ) );
}


Q_EXPORT_PLUGIN2( Hatchet::InfoSystem::InfoPlugin, Hatchet::InfoSystem::MusixMatchPlugin )
