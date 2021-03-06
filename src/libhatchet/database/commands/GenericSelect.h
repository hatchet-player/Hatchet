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

#ifndef DATABASECOMMAND_GENERICSELECT_H
#define DATABASECOMMAND_GENERICSELECT_H

#include <QVariantMap>

#include "database/DatabaseCommand.h"
#include "Typedefs.h"

#include <QStringList>
#include <QMetaType>

#include "DllMacro.h"

namespace Hatchet
{

/**
 * This dbcmd takes a generic SELECT command that operates on the database and returns a list of query_ptrs
 *  that match.
 *
 * In order for the conversion to query_ptr to work, the SELECT command should select the following items:
 *
 * track query:
 *      track.name, artist.name [, optional extra values ]
 *
 *  artist query:
 *      artist.id, artist.name [, optional extra values ]
 *
 *  album query:
 *      album.id, album.name, artist.id, artist.name [, optional extra values ]
 *
 * Any extra values in the resultset will be returned as a QVariantList attached to the "data" property of each query_ptr
 *
 * Notes:
 *      * Do not trail your SQL command with ;
 *      * Do not use the LIMIT command if you pass limitResults > -1
 *
 */
class DLLEXPORT DatabaseCommand_GenericSelect : public DatabaseCommand
{
    Q_OBJECT

public:
    enum QueryType {
        Track,
        Artist,
        Album
    };

    explicit DatabaseCommand_GenericSelect( const QString& sqlSelect, QueryType type, int limitResults = -1, QObject* parent = 0 );
    explicit DatabaseCommand_GenericSelect( const QString& sqlSelect, QueryType type, bool rawData, QObject* parent = 0 );
    virtual void exec( DatabaseImpl* lib );
    virtual bool doesMutates() const { return false; }

    virtual QString commandname() const { return "genericselect"; }

signals:
    void tracks( const QList< Hatchet::query_ptr >& tracks );
    void artists( const QList< Hatchet::artist_ptr >& artists );
    void albums( const QList< Hatchet::album_ptr >& albums );

    void rawData( const QList< QStringList >& data );
private:
    QString m_sqlSelect;
    QueryType m_queryType;
    int m_limit;
    bool m_raw;
};

}

#endif // DATABASECOMMAND_GENERICSELECT_H
