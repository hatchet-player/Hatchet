/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef HATCHETSQLQUERY_H
#define HATCHETSQLQUERY_H

// subclass QSqlQuery so that it prints the error msg if a query fails

#include <QSqlDriver>
#include <QSqlQuery>

//#define HATCHET_QUERY_ANALYZE 1

#include "DllMacro.h"

class DLLEXPORT HatchetSqlQuery : public QSqlQuery
{

public:
    HatchetSqlQuery();
    HatchetSqlQuery( const QSqlDatabase& db );

    static QString escape( QString identifier );

    bool prepare( const QString& query );
    bool exec( const QString& query );
    bool exec();

    bool commitTransaction();

private:
    bool isBusyError( const QSqlError& error ) const;

    void showError();

    QSqlDatabase m_db;
    QString m_query;
};

#endif // HATCHETSQLQUERY_H
