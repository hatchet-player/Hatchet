/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2013, Uwe L. Korn <uwelk@xhochy.com>
 *
 *   Hatchet is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hatchet is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hatchet. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ENTITYTIME_H
#define ENTITYTIME_H

#include <jreen/stanzaextension.h>

#include "sip/SipInfo.h"

#define HATCHET_SIP_MESSAGE_NS QLatin1String("http://www.tomhawk-player.org/sip/transports")

#include "accounts/AccountDllMacro.h"

class ACCOUNTDLLEXPORT HatchetXmppMessage : public Jreen::Payload
{
    J_PAYLOAD(HatchetXmppMessage)
    public:
        HatchetXmppMessage();
        HatchetXmppMessage(const QList<SipInfo>& sipInfos);
        ~HatchetXmppMessage();

        /**
         * The SipInfo objects that are wrapped in this XmppMessage
         */
        const QList<SipInfo> sipInfos() const;

        /**
         * The name of the peer contained in this message
         */
        const QString key() const;

        /**
         * The name of the peer contained in this message
         */
        const QString uniqname() const;

    private:
        QList<SipInfo> m_sipInfos;
};

#endif // ENTITYTIME_H
