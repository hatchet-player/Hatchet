/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2012, Leo Franchi            <lfranchi@kde.org>
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

#ifndef LASTFMPLUGIN_H
#define LASTFMPLUGIN_H

#include "infosystem/InfoSystem.h"
#include "infosystem/InfoSystemWorker.h"
#include "DllMacro.h"

#include <lastfm5/Track.h>
#include <lastfm5/Audioscrobbler.h>
#include <lastfm5/ScrobblePoint.h>

#include <QObject>

class QNetworkReply;

namespace Hatchet
{

namespace Accounts
{
    class LastFmAccount;
}

namespace InfoSystem
{

class DLLEXPORT LastFmInfoPlugin : public InfoPlugin
{
    Q_OBJECT

public:
    LastFmInfoPlugin( Accounts::LastFmAccount* account );
    virtual ~LastFmInfoPlugin();

    const QString friendlyName() const { return "LastFM"; };

public slots:
    void settingsChanged();

    void onAuthenticated();
    void coverArtReturned();
    void artistImagesReturned();
    void similarArtistsReturned();
    void topTracksReturned();
    void artistInfoReturned();
    void albumInfoReturned();
    void chartReturned();
    void similarTracksReturned();

protected slots:
    virtual void init();
    virtual void getInfo( Hatchet::InfoSystem::InfoRequestData requestData );
    virtual void notInCacheSlot( Hatchet::InfoSystem::InfoStringHash criteria, Hatchet::InfoSystem::InfoRequestData requestData );

    virtual void pushInfo( Hatchet::InfoSystem::InfoPushData pushData );

private:
    void fetchSimilarArtists( Hatchet::InfoSystem::InfoRequestData requestData );
    void fetchTopTracks( Hatchet::InfoSystem::InfoRequestData requestData );
    void fetchArtistInfo( Hatchet::InfoSystem::InfoRequestData requestData );
    void fetchAlbumInfo( Hatchet::InfoSystem::InfoRequestData requestData );
    void fetchChart( Hatchet::InfoSystem::InfoRequestData requestData );
    void fetchChartCapabilities( Hatchet::InfoSystem::InfoRequestData requestData );
    void fetchSimilarTracks( Hatchet::InfoSystem::InfoRequestData requestData );

    void createScrobbler();
    void nowPlaying( const QVariant& input );
    void scrobble();
    void sendLoveSong( const InfoType type, QVariant input );

    void dataError( Hatchet::InfoSystem::InfoRequestData requestData );

    QPointer< Accounts::LastFmAccount > m_account;
    QList<lastfm::Track> parseTrackList( QNetworkReply* reply );

    lastfm::MutableTrack m_track;
    lastfm::Audioscrobbler* m_scrobbler;
    QString m_pw;

    QList< QUrl > m_badUrls;
};

}

}

#endif // LASTFMPLUGIN_H
