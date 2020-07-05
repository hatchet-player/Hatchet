/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2011,      Leo Franchi <lfranchi@kde.org>
 *   Copyright 2011,      Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2011-2016, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2013,      Uwe L. Korn <uwelk@xhochy.com>
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

#pragma once
#ifndef HATCHET_UTILS_SHORTLINKHELPER_H
#define HATCHET_UTILS_SHORTLINKHELPER_H

#include "DllMacro.h"
#include "Typedefs.h"

namespace Hatchet {
namespace Utils {

class ShortLinkHelperPrivate;

class DLLEXPORT ShortLinkHelper : public QObject
{
    Q_OBJECT
public:
    explicit ShortLinkHelper( QObject *parent = 0 );
    virtual ~ShortLinkHelper();

    QString hostname() const;

public slots:
    void shortLink( const Hatchet::playlist_ptr& playlist );
    void shortenLink( const QUrl& url, const QVariant &callbackObj = QVariant() );

signals:
    void shortLinkReady( const Hatchet::playlist_ptr& playlist, const QUrl& shortUrl );
    void shortLinkReady( const QUrl& longUrl, const QUrl& shortUrl, const QVariant& callbackObj );
    void done();

protected:
    QScopedPointer<ShortLinkHelperPrivate> d_ptr;

private slots:
    void shortLinkRequestFinished( const Hatchet::playlist_ptr& playlist );
    void shortenLinkRequestFinished();
    void shortenLinkRequestError( QNetworkReply::NetworkError );

private:
    Q_DECLARE_PRIVATE( ShortLinkHelper )
};

} // namespace Utils
} // namespace Hatchet

#endif // HATCHET_UTILS_SHORTLINKHELPER_H
