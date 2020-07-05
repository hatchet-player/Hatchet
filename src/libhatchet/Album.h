/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2013,      Uwe L. Korn  <uwelk@xhochy.com>
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
#ifndef HATCHETALBUM_H
#define HATCHETALBUM_H

#include <QPixmap>
#include <QFuture>

#include "infosystem/InfoSystem.h"
#include "DllMacro.h"
#include "Typedefs.h"


namespace Hatchet
{

class AlbumPrivate;
class IdThreadWorker;

class DLLEXPORT Album : public QObject
{
Q_OBJECT

public:
    static album_ptr get( const Hatchet::artist_ptr& artist, const QString& name, bool autoCreate = false );
    static album_ptr get( unsigned int id, const QString& name, const Hatchet::artist_ptr& artist );

    Album( unsigned int id, const QString& name, const Hatchet::artist_ptr& artist );
    Album( const QString& name, const Hatchet::artist_ptr& artist );
    virtual ~Album();

    unsigned int id() const;
    QString name() const;
    QString sortname() const;

    artist_ptr artist() const;
    QPixmap cover( const QSize& size, bool forceLoad = true ) const;
    bool coverLoaded() const;
    QString purchaseUrl() const;
    bool purchased() const;

    QList<Hatchet::query_ptr> tracks( ModelMode mode = Mixed, const Hatchet::collection_ptr& collection = Hatchet::collection_ptr() );
    Hatchet::playlistinterface_ptr playlistInterface( ModelMode mode, const Hatchet::collection_ptr& collection = Hatchet::collection_ptr() );

    QWeakPointer< Hatchet::Album > weakRef();
    void setWeakRef( QWeakPointer< Hatchet::Album > weakRef );

    void loadId( bool autoCreate );

public slots:
    void deleteLater();

signals:
    void tracksAdded( const QList<Hatchet::query_ptr>& tracks, Hatchet::ModelMode mode, const Hatchet::collection_ptr& collection );
    void updated();
    void coverChanged();

protected:
    QScopedPointer<AlbumPrivate> d_ptr;

private slots:
    void onTracksLoaded( Hatchet::ModelMode mode, const Hatchet::collection_ptr& collection );

    void infoSystemInfo( const Hatchet::InfoSystem::InfoRequestData& requestData, const QVariant& output );
    void infoSystemFinished( const QString& target );

private:
    Q_DECLARE_PRIVATE( Album )
    Q_DISABLE_COPY( Album )
    QString infoid() const;
    void setIdFuture( QFuture<unsigned int> future );

    static QHash< QString, album_wptr > s_albumsByName;
    static QHash< unsigned int, album_wptr > s_albumsById;

    friend class IdThreadWorker;
};

} // ns

Q_DECLARE_METATYPE( Hatchet::album_ptr )

#endif
