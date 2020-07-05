/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Teo Mrnjavac <teo@kde.org>
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

#ifndef DATABASECOMMAND_SHARETRACK_H
#define DATABASECOMMAND_SHARETRACK_H

#include <QObject>
#include <QVariantMap>

#include "SocialAction.h"
#include "SourceList.h"
#include "Typedefs.h"

#include "DllMacro.h"

namespace Hatchet
{

class DLLEXPORT DatabaseCommand_ShareTrack : public DatabaseCommand_SocialAction
{
    Q_OBJECT
    Q_PROPERTY( QString recipient   READ recipient  WRITE setRecipient )

public:
    explicit DatabaseCommand_ShareTrack( QObject* parent = nullptr );

    explicit DatabaseCommand_ShareTrack( const Hatchet::trackdata_ptr& track,
                                         const QString& recipientDbid,
                                         QObject* parent = nullptr );

    QString commandname() const override;

    void exec( DatabaseImpl* ) override;
    void postCommitHook() override;

    bool doesMutates() const override;
    bool singletonCmd() const override;
    bool localOnly() const override;
    bool groupable() const override;

    QString recipient() const;
    void setRecipient( const QString& s );

private:
    QString m_recipient;
};

}

#endif // DATABASECOMMAND_SHARETRACK_H
