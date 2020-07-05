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

#ifndef ECHONESTPLUGIN_H
#define ECHONESTPLUGIN_H

#include "../../InfoPluginDllMacro.h"

#include "infosystem/InfoSystem.h"
#include "infosystem/InfoSystemWorker.h"

#include <echonest5/Artist.h>

#include <QObject>

class QNetworkReply;

namespace Hatchet
{

namespace InfoSystem
{

class INFOPLUGINDLLEXPORT EchonestPlugin : public InfoPlugin
{
    Q_PLUGIN_METADATA( IID "org.hatchet-player.Player.InfoPlugin" )
    Q_OBJECT
    Q_INTERFACES( Hatchet::InfoSystem::InfoPlugin )

public:
    EchonestPlugin();
    virtual ~EchonestPlugin();

protected slots:
    virtual void init();
    
    virtual void getInfo( Hatchet::InfoSystem::InfoRequestData requestData );

    virtual void pushInfo( Hatchet::InfoSystem::InfoPushData pushData )
    {
        Q_UNUSED( pushData );
    }

    virtual void notInCacheSlot( Hatchet::InfoSystem::InfoStringHash criteria, Hatchet::InfoSystem::InfoRequestData requestData )
    {
        Q_UNUSED( criteria );
        Q_UNUSED( requestData );
    }

private:
    void getSongProfile( const Hatchet::InfoSystem::InfoRequestData &requestData, const QString &item = QString() );
    void getArtistBiography( const Hatchet::InfoSystem::InfoRequestData &requestData );
    void getArtistFamiliarity( const Hatchet::InfoSystem::InfoRequestData &requestData );
    void getArtistHotttnesss( const Hatchet::InfoSystem::InfoRequestData &requestData );
    void getArtistTerms( const Hatchet::InfoSystem::InfoRequestData &requestData );
    void getMiscTopTerms( const Hatchet::InfoSystem::InfoRequestData &requestData );

    bool isValidArtistData( const Hatchet::InfoSystem::InfoRequestData &requestData );
    bool isValidTrackData( const Hatchet::InfoSystem::InfoRequestData &requestData );
    Echonest::Artist artistFromReply( QNetworkReply* );

private slots:
    void getArtistBiographySlot();
    void getArtistFamiliaritySlot();
    void getArtistHotttnesssSlot();
    void getArtistTermsSlot();
    void getMiscTopSlot();
};

}

}

#endif // ECHONESTPLUGIN_H
