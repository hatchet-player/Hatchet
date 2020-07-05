/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org
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

#ifndef JSPFLOADER_H
#define JSPFLOADER_H

#include <QObject>
#include <QUrl>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "Playlist.h"
#include "Typedefs.h"

#include "DllMacro.h"

namespace Hatchet
{

class DLLEXPORT JSPFLoader : public QObject
{
Q_OBJECT

public:
    explicit JSPFLoader( bool autoCreate = true, QObject* parent = 0 );

    virtual ~JSPFLoader();

    QList< Hatchet::query_ptr > entries() const;
    void setOverrideTitle( const QString& newTitle ) { m_overrideTitle = newTitle; }

    void setAutoDelete( bool autoDelete ) { m_autoDelete = autoDelete; }

signals:
    void failed();
    void ok( const Hatchet::playlist_ptr& );
    void tracks( const QList< Hatchet::query_ptr > tracks );

public slots:
    void load( const QUrl& url );
    void load( QFile& file );

private slots:
    void networkLoadFinished();
    void networkError( QNetworkReply::NetworkError e );

private:
    void reportError();
    void gotBody();

    bool m_autoCreate, m_autoDelete;
    QList< Hatchet::query_ptr > m_entries;
    QString m_title, m_info, m_creator, m_overrideTitle;

    QByteArray m_body;
    Hatchet::playlist_ptr m_playlist;
};

}

#endif // JSPFLOADER_H
