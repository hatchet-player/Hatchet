/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2015, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
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

#include "Album_p.h"

#include "database/Database.h"
#include "database/DatabaseImpl.h"
#include "database/IdThreadWorker.h"
#include "utils/HatchetUtilsGui.h"
#include "utils/Logger.h"

#include "Artist.h"
#include "AlbumPlaylistInterface.h"
#include "PlaylistEntry.h"
#include "Query.h"
#include "Source.h"

#include <QReadWriteLock>
#include <QPixmapCache>
#include <QCoreApplication>

using namespace Hatchet;

QHash< QString, album_wptr > Album::s_albumsByName = QHash< QString, album_wptr >();
QHash< unsigned int, album_wptr > Album::s_albumsById = QHash< unsigned int, album_wptr >();

static QMutex s_nameCacheMutex;
static QReadWriteLock s_idMutex;


Album::~Album()
{
    Q_D( Album );
    d->ownRef.clear();

    delete d->cover;
}


inline QString
albumCacheKey( const Hatchet::artist_ptr& artist, const QString& albumName )
{
    return QString( "%1\t\t%2" ).arg( artist->name().toLower() ).arg( albumName.toLower() );
}


album_ptr
Album::get( const Hatchet::artist_ptr& artist, const QString& name, bool autoCreate )
{
    if ( !Database::instance() || !Database::instance()->impl() )
        return album_ptr();

    QMutexLocker lock( &s_nameCacheMutex );
    const QString key = albumCacheKey( artist, name );
    if ( s_albumsByName.contains( key ) )
    {
        album_wptr album = s_albumsByName.value( key );
        if ( album )
            return album.toStrongRef();
    }

    album_ptr album = album_ptr( new Album( name, artist ), &Album::deleteLater );
    album->moveToThread( QCoreApplication::instance()->thread() );
    album->setWeakRef( album.toWeakRef() );
    album->loadId( autoCreate );
    s_albumsByName.insert( key, album );

    return album;
}


album_ptr
Album::get( unsigned int id, const QString& name, const Hatchet::artist_ptr& artist )
{
    s_idMutex.lockForRead();
    if ( s_albumsById.contains( id ) )
    {
        album_wptr album = s_albumsById.value( id );
        s_idMutex.unlock();

        if ( album )
            return album;
    }
    s_idMutex.unlock();

    QMutexLocker lock( &s_nameCacheMutex );
    const QString key = albumCacheKey( artist, name );
    if ( s_albumsByName.contains( key ) )
    {
        album_wptr album = s_albumsByName.value( key );
        if ( album )
            return album;
    }

    album_ptr a = album_ptr( new Album( id, name, artist ), &Album::deleteLater );
    a->setWeakRef( a.toWeakRef() );
    s_albumsByName.insert( key, a );

    if ( id > 0 )
    {
        s_idMutex.lockForWrite();
        s_albumsById.insert( id, a );
        s_idMutex.unlock();
    }

    return a;
}


Album::Album( unsigned int id, const QString& name, const Hatchet::artist_ptr& artist )
    : d_ptr( new AlbumPrivate( this, id, name, artist ) )
{
    Q_D( Album );
    d->sortname = DatabaseImpl::sortname( name );
}


Album::Album( const QString& name, const Hatchet::artist_ptr& artist )
    : d_ptr( new AlbumPrivate( this, name, artist ) )
{
    Q_D( Album );
    d->sortname = DatabaseImpl::sortname( name );
}


void
Album::deleteLater()
{
    Q_D( Album );
    QMutexLocker lock( &s_nameCacheMutex );

    const QString key = albumCacheKey( d->artist, d->name );
    if ( s_albumsByName.contains( key ) )
    {
        s_albumsByName.remove( key );
    }

    if ( d->id > 0 )
    {
        s_idMutex.lockForWrite();
        if ( s_albumsById.contains( d->id ) )
        {
            s_albumsById.remove( d->id );
        }
        s_idMutex.unlock();
    }

    QObject::deleteLater();
}


void
Album::onTracksLoaded( Hatchet::ModelMode mode, const Hatchet::collection_ptr& collection )
{
    emit tracksAdded( playlistInterface( mode, collection )->tracks(), mode, collection );
}


artist_ptr
Album::artist() const
{
    Q_D( const Album );
    return d->artist;
}


void
Album::loadId( bool autoCreate )
{
    Q_D( Album );
    Q_ASSERT( d->waitingForId );
    IdThreadWorker::getAlbumId( d->ownRef.toStrongRef(), autoCreate );
}


void
Album::setIdFuture( QFuture<unsigned int> future )
{
    Q_D( Album );
    d->idFuture = future;
}


unsigned int
Album::id() const
{
    Q_D( const Album );
    s_idMutex.lockForRead();
    const bool waiting = d->waitingForId;
    s_idMutex.unlock();

    if ( waiting )
    {
        d->idFuture.waitForFinished();

        s_idMutex.lockForWrite();
        d->id = d->idFuture.result();
        d->waitingForId = false;

        if ( d->id > 0 )
            s_albumsById.insert( d->id, d->ownRef.toStrongRef() );

        s_idMutex.unlock();
    }

    return d->id;
}


QString
Album::name() const
{
    Q_D( const Album );
    return d->name;
}


QString
Album::sortname() const
{
    Q_D( const Album );
    return d->sortname;
}


QString
Album::purchaseUrl() const
{
    Q_D( const Album );
    if ( !d->purchaseUrlLoaded )
    {
        Hatchet::InfoSystem::InfoStringHash albumInfo;
        albumInfo["artist"] = d->artist->name();
        albumInfo["album"] = d->name;

        Hatchet::InfoSystem::InfoRequestData requestData;
        requestData.caller = infoid();
        requestData.type = Hatchet::InfoSystem::InfoAlbumPurchaseUrl;
        requestData.input = QVariant::fromValue< Hatchet::InfoSystem::InfoStringHash >( albumInfo );
        requestData.customData = QVariantMap();
        requestData.allSources = true;

        connect( Hatchet::InfoSystem::InfoSystem::instance(),
                SIGNAL( info( Hatchet::InfoSystem::InfoRequestData, QVariant ) ),
                SLOT( infoSystemInfo( Hatchet::InfoSystem::InfoRequestData, QVariant ) ) );

        connect( Hatchet::InfoSystem::InfoSystem::instance(),
                SIGNAL( finished( QString ) ),
                SLOT( infoSystemFinished( QString ) ) );

        Hatchet::InfoSystem::InfoSystem::instance()->getInfo( requestData );
    }

    return d->purchaseUrl;
}


bool
Album::purchased() const
{
    Q_D( const Album );
    return d->purchased;
}


QPixmap
Album::cover( const QSize& size, bool forceLoad ) const
{
    Q_D( const Album );
    if ( d->name.isEmpty() )
    {
        d->coverLoaded = true;
        return QPixmap();
    }

    if ( !d->coverLoaded && !d->coverLoading )
    {
        if ( !forceLoad )
            return QPixmap();

        Hatchet::InfoSystem::InfoStringHash trackInfo;
        trackInfo["artist"] = d->artist->name();
        trackInfo["album"] = d->name;

        Hatchet::InfoSystem::InfoRequestData requestData;
        requestData.caller = infoid();
        requestData.type = Hatchet::InfoSystem::InfoAlbumCoverArt;
        requestData.input = QVariant::fromValue< Hatchet::InfoSystem::InfoStringHash >( trackInfo );
        requestData.customData = QVariantMap();
        requestData.allSources = true;

        connect( Hatchet::InfoSystem::InfoSystem::instance(),
                SIGNAL( info( Hatchet::InfoSystem::InfoRequestData, QVariant ) ),
                SLOT( infoSystemInfo( Hatchet::InfoSystem::InfoRequestData, QVariant ) ) );

        connect( Hatchet::InfoSystem::InfoSystem::instance(),
                SIGNAL( finished( QString ) ),
                SLOT( infoSystemFinished( QString ) ) );

        Hatchet::InfoSystem::InfoSystem::instance()->getInfo( requestData );

        d->coverLoading = true;
    }

    if ( !d->cover && !d->coverBuffer.isEmpty() )
    {
        QPixmap cover;
        cover.loadFromData( d->coverBuffer );
        d->coverBuffer.clear();

        d->cover = new QPixmap( HatchetUtils::squareCenterPixmap( cover ) );
    }

    if ( d->cover && !d->cover->isNull() && !size.isEmpty() )
    {
        const QString cacheKey = QString( "%1_%2_%3" ).arg( infoid() ).arg( size.width() ).arg( size.height() );
        QPixmap cover;

        if ( !QPixmapCache::find( cacheKey, &cover ) )
        {
            cover = d->cover->scaled( size, Qt::KeepAspectRatio, Qt::SmoothTransformation );
            QPixmapCache::insert( cacheKey, cover );
            return cover;
        }
        return cover;
    }

    if ( d->cover )
        return *d->cover;
    else
        return QPixmap();
}


bool
Album::coverLoaded() const
{
    Q_D( const Album );
    return d->coverLoaded;
}


void
Album::infoSystemInfo( const Hatchet::InfoSystem::InfoRequestData& requestData, const QVariant& output )
{
    Q_D( Album );
    if ( requestData.caller != infoid() )
        return;

    if ( requestData.type == Hatchet::InfoSystem::InfoAlbumPurchaseUrl && output.isValid() )
    {
        QVariantMap returnedData = output.value< QVariantMap >();
        d->purchaseUrlLoaded = true;
        d->purchaseUrl = returnedData["url"].toString();
        d->purchased = returnedData["purchased"].toBool();
        emit updated();
        return;
    }

    if ( requestData.type != Hatchet::InfoSystem::InfoAlbumCoverArt )
    {
        return;
    }

    if ( output.isNull() )
    {
        d->coverLoaded = true;
    }
    else if ( output.isValid() )
    {
        QVariantMap returnedData = output.value< QVariantMap >();
        const QByteArray ba = returnedData["imgbytes"].toByteArray();
        if ( !ba.isEmpty() )
        {
            d->coverBuffer = ba;
        }

        d->coverLoaded = true;
        emit coverChanged();
    }
}


void
Album::infoSystemFinished( const QString& target )
{
    Q_D( Album );
    if ( target != infoid() )
        return;

    disconnect( Hatchet::InfoSystem::InfoSystem::instance(), SIGNAL( info( Hatchet::InfoSystem::InfoRequestData, QVariant ) ),
                this, SLOT( infoSystemInfo( Hatchet::InfoSystem::InfoRequestData, QVariant ) ) );

    disconnect( Hatchet::InfoSystem::InfoSystem::instance(), SIGNAL( finished( QString ) ),
                this, SLOT( infoSystemFinished( QString ) ) );

    d->coverLoading = false;
    emit updated();
}


Hatchet::playlistinterface_ptr
Album::playlistInterface( ModelMode mode, const Hatchet::collection_ptr& collection )
{
    Q_D( Album );
    playlistinterface_ptr pli = d->playlistInterface[ mode ][ collection ];

    if ( pli.isNull() )
    {
        pli = Hatchet::playlistinterface_ptr( new Hatchet::AlbumPlaylistInterface( this, mode, collection ) );
        connect( pli.data(), SIGNAL( tracksLoaded( Hatchet::ModelMode, Hatchet::collection_ptr ) ),
                               SLOT( onTracksLoaded( Hatchet::ModelMode, Hatchet::collection_ptr ) ) );

        d->playlistInterface[ mode ][ collection ] = pli;
    }

    return pli;
}


QWeakPointer<Album>
Album::weakRef()
{
    Q_D( Album );
    return d->ownRef;
}


void
Album::setWeakRef( QWeakPointer<Album> weakRef )
{
    Q_D( Album );
    d->ownRef = weakRef;
}


QList<Hatchet::query_ptr>
Album::tracks( ModelMode mode, const Hatchet::collection_ptr& collection )
{
    return playlistInterface( mode, collection )->tracks();
}


QString
Album::infoid() const
{
    Q_D( const Album );
    if ( d->uuid.isEmpty() )
        d->uuid = uuid();

    return d->uuid;
}
