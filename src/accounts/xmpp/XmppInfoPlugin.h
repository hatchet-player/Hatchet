/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012, Dominik Schmidt <domme@tomahawk-player.org>
 *   Copyright 2012, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef XMPPINFOPLUGIN_H
#define XMPPINFOPLUGIN_H

#include "infosystem/InfoSystem.h"

#include <QTimer>

class XmppSipPlugin;

namespace Hatchet {

    namespace InfoSystem {

        class XmppInfoPlugin  : public InfoPlugin
        {
            Q_OBJECT

        public:
            XmppInfoPlugin(XmppSipPlugin* parent);
            virtual ~XmppInfoPlugin();

            const QString friendlyName() const override;

        signals:
            void publishTune( QUrl url, Hatchet::InfoSystem::InfoStringHash trackInfo );

        public slots:
            void notInCacheSlot( const Hatchet::InfoSystem::InfoStringHash criteria, Hatchet::InfoSystem::InfoRequestData requestData ) override;

        protected slots:
            void init() override;
            void pushInfo( Hatchet::InfoSystem::InfoPushData pushData ) override;
            void getInfo( Hatchet::InfoSystem::InfoRequestData requestData ) override;

        private slots:
            void audioStarted( const Hatchet::InfoSystem::PushInfoPair& pushInfoPair );
            void audioStopped();
            void audioPaused();
            void onQueryLinkReady( const QVariantMap& data );

        private:
            QPointer< XmppSipPlugin > m_sipPlugin;
            QTimer m_pauseTimer;
        };

    }

}

#endif // XMPPINFOPLUGIN_H
