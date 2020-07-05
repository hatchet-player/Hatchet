/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012 Leo Franchi <lfranchi@kde.org>
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

#ifndef SPOTIFYINFOPLUGIN_H
#define SPOTIFYINFOPLUGIN_H

#include "infosystem/InfoSystem.h"
#include "DllMacro.h"

#include <QPointer>

class QNetworkReply;

namespace Hatchet
{

namespace Accounts
{
    class SpotifyAccount;
}

namespace InfoSystem
{

class DLLEXPORT SpotifyInfoPlugin : public InfoPlugin
{
    Q_OBJECT

public:
    explicit SpotifyInfoPlugin( Accounts::SpotifyAccount* account );
    virtual ~SpotifyInfoPlugin();

    const QString friendlyName() const { return "Spotify"; };

public slots:
    void  albumListingResult( const QString& msgType, const QVariantMap& msg, const QVariant& extraData );

protected slots:
    virtual void init() {}
    virtual void getInfo( Hatchet::InfoSystem::InfoRequestData requestData );
    virtual void notInCacheSlot( Hatchet::InfoSystem::InfoStringHash criteria, Hatchet::InfoSystem::InfoRequestData requestData );
    virtual void pushInfo( Hatchet::InfoSystem::InfoPushData  );

private slots:
    void albumIdLookupFinished( QNetworkReply* reply, const Hatchet::InfoSystem::InfoRequestData& requestData );
    void albumContentsLookupFinished( QNetworkReply* reply, const Hatchet::InfoSystem::InfoRequestData& requestData );

private:
    void dataError( InfoRequestData );
    void trackListResult( const QStringList& trackNameList, const Hatchet::InfoSystem::InfoRequestData& requestData );
    void sendLoveSong( const InfoType type, QVariant input );

    QPointer< Hatchet::Accounts::SpotifyAccount > m_account;
};

}

}

#endif // SPOTIFYINFOPLUGIN_H
