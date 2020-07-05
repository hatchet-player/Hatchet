/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
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

#ifndef DATABASECOMMAND_SETTRACKATTRIBUTES
#define DATABASECOMMAND_SETTRACKATTRIBUTES

#include "Typedefs.h"
#include "DatabaseCommandLoggable.h"

#include <QByteArray>

namespace Hatchet
{

class DatabaseCommand_SetTrackAttributes : public DatabaseCommandLoggable
{
    Q_OBJECT
public:
    enum AttributeType {
        EchonestCatalogId = 0,
    };

    // Takes a list of <track_id, value> pairs. key is always type
    DatabaseCommand_SetTrackAttributes( AttributeType type, QList< QPair< Hatchet::QID, QString > > ids, bool toDelete = false );
    // Deletes *all tracks with attribute*
    DatabaseCommand_SetTrackAttributes( AttributeType type );
    DatabaseCommand_SetTrackAttributes() {} // JSON

    virtual void exec( DatabaseImpl* lib );
    virtual bool doesMutates() const { return true; }
    virtual bool loggable() const { return m_loggable; }

    virtual QString commandname() const { return "settrackattributes"; }

    void setType( int type ) { m_type = (AttributeType)type; }
    int type() const { return (int)m_type; }

private:
    bool m_loggable, m_delete;

    AttributeType m_type;
    QList< QPair< Hatchet::QID, QString > > m_tracks;
};

}

#endif // DATABASECOMMAND_SETTRACKATTRIBUTES
