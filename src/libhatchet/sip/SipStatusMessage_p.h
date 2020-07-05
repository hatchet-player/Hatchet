/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Dominik Schmidt <domme@tomahawk-player.org>
 *   Copyright 2013, Uwe L. Korn <uwelk@xhochy.com>
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

#ifndef SIPSTATUSMESSAGE_P_H
#define SIPSTATUSMESSAGE_P_H

#include "SipStatusMessage.h"

#include <QHash>

class QTimer;

class SipStatusMessagePrivate
{
public:
    SipStatusMessagePrivate( SipStatusMessage* q, SipStatusMessage::SipStatusMessageType _statusMessageType, const QString& _contactId, const QString& _message )
        : q_ptr ( q )
        , contactId( _contactId )
        , statusMessageType( _statusMessageType )
        , message( _message )

    {
    }
    SipStatusMessage* q_ptr;
    Q_DECLARE_PUBLIC ( SipStatusMessage )

private:
    QString contactId;
    SipStatusMessage::SipStatusMessageType statusMessageType;
    QString message;

    static QHash< SipStatusMessage::SipStatusMessageType, QPixmap > s_typesPixmaps;

    QTimer* timer;
};


#endif // SIPSTATUSMESSAGE_P_H
