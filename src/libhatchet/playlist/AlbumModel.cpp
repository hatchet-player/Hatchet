/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2015, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
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

#include "AlbumModel.h"

#include <QListView>
#include <QMimeData>
#include <QNetworkReply>

#include "Artist.h"
#include "PlayableItem.h"
#include "Source.h"
#include "SourceList.h"
#include "database/Database.h"
#include "utils/HatchetUtils.h"
#include "utils/Logger.h"

using namespace Hatchet;


AlbumModel::AlbumModel( QObject* parent )
    : PlayableModel( parent )
    , m_overwriteOnAdd( false )
{
}


AlbumModel::~AlbumModel()
{
}


void
AlbumModel::addCollection( const collection_ptr& collection, bool overwrite )
{
    DatabaseCommand_AllAlbums* cmd = new DatabaseCommand_AllAlbums( collection );
    m_overwriteOnAdd = overwrite;
    m_collection = collection;

    connect( cmd, SIGNAL( albums( QList<Hatchet::album_ptr>, QVariant ) ),
                    SLOT( addAlbums( QList<Hatchet::album_ptr> ) ) );

    Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );

    setTitle( tr( "All albums from %1" ).arg( collection->prettyName() ) );

    if ( collection.isNull() )
    {
        connect( SourceList::instance(), SIGNAL( sourceAdded( Hatchet::source_ptr ) ), SLOT( onSourceAdded( Hatchet::source_ptr ) ), Qt::UniqueConnection );

        QList<Hatchet::source_ptr> sources = SourceList::instance()->sources();
        foreach ( const source_ptr& source, sources )
        {
            connect( source->dbCollection().data(), SIGNAL( changed() ), SLOT( onCollectionChanged() ), Qt::UniqueConnection );
        }
    }
    else
    {
        connect( collection.data(), SIGNAL( changed() ), SLOT( onCollectionChanged() ), Qt::UniqueConnection );
    }

    emit loadingStarted();
}


void
AlbumModel::addFilteredCollection( const collection_ptr& collection, unsigned int amount, DatabaseCommand_AllAlbums::SortOrder order, bool overwrite )
{
    DatabaseCommand_AllAlbums* cmd = new DatabaseCommand_AllAlbums( collection );
    cmd->setLimit( amount );
    cmd->setSortOrder( order );
    cmd->setSortDescending( true );
    m_overwriteOnAdd = overwrite;
    m_collection = collection;

    connect( cmd, SIGNAL( albums( QList<Hatchet::album_ptr>, QVariant ) ),
                    SLOT( addAlbums( QList<Hatchet::album_ptr> ) ) );

    Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );

    if ( !collection.isNull() )
        setTitle( tr( "All albums from %1" ).arg( collection->prettyName() ) );
    else
        setTitle( tr( "All albums" ) );

    emit loadingStarted();
}


void
AlbumModel::addAlbums( const QList<Hatchet::album_ptr>& albums )
{
    emit loadingFinished();

    if ( m_overwriteOnAdd )
        clear();

    QList<Hatchet::album_ptr> trimmedAlbums;
    foreach ( const album_ptr& album, albums )
    {
        if ( !album.isNull() && !album->name().isEmpty() )
        {
            if ( findItem( album ) || trimmedAlbums.contains( album ) )
                continue;
            trimmedAlbums << album;
        }
    }

    if ( trimmedAlbums.isEmpty() )
    {
        emit itemCountChanged( rowCount( QModelIndex() ) );
        return;
    }

    int c = rowCount( QModelIndex() );
    QPair< int, int > crows;
    crows.first = c;
    crows.second = c + trimmedAlbums.count() - 1;

    emit beginInsertRows( QModelIndex(), crows.first, crows.second );

    foreach( const album_ptr& album, trimmedAlbums )
    {
        PlayableItem* albumitem = new PlayableItem( album, rootItem() );
        albumitem->index = createIndex( rootItem()->children.count() - 1, 0, albumitem );

        connect( albumitem, SIGNAL( dataChanged() ), SLOT( onDataChanged() ) );
    }

    emit endInsertRows();
    emit itemCountChanged( rowCount( QModelIndex() ) );
}


void
AlbumModel::addArtists( const QList<Hatchet::artist_ptr>& artists )
{
    emit loadingFinished();

    if ( m_overwriteOnAdd )
        clear();

    QList<Hatchet::artist_ptr> trimmedArtists;
    foreach ( const artist_ptr& artist, artists )
    {
        if ( !artist.isNull() && !artist->name().isEmpty() )
        {
            if ( findItem( artist ) || trimmedArtists.contains( artist ) )
                continue;
            trimmedArtists << artist;
        }
    }

    if ( trimmedArtists.isEmpty() )
    {
        emit itemCountChanged( rowCount( QModelIndex() ) );
        return;
    }

    int c = rowCount( QModelIndex() );
    QPair< int, int > crows;
    crows.first = c;
    crows.second = c + trimmedArtists.count() - 1;

    emit beginInsertRows( QModelIndex(), crows.first, crows.second );

    foreach ( const artist_ptr& artist, trimmedArtists )
    {
        PlayableItem* albumitem = new PlayableItem( artist, rootItem() );
        albumitem->index = createIndex( rootItem()->children.count() - 1, 0, albumitem );

        connect( albumitem, SIGNAL( dataChanged() ), SLOT( onDataChanged() ) );
    }

    emit endInsertRows();
    emit itemCountChanged( rowCount( QModelIndex() ) );
}


void
AlbumModel::addQueries( const QList<Hatchet::query_ptr>& queries )
{
    emit loadingFinished();

    if ( m_overwriteOnAdd )
        clear();

    int c = rowCount( QModelIndex() );
    QPair< int, int > crows;
    crows.first = c;
    crows.second = c + queries.count() - 1;

    emit beginInsertRows( QModelIndex(), crows.first, crows.second );

    foreach ( const query_ptr& query, queries )
    {
        PlayableItem* albumitem = new PlayableItem( query, rootItem() );
        albumitem->index = createIndex( rootItem()->children.count() - 1, 0, albumitem );

        connect( albumitem, SIGNAL( dataChanged() ), SLOT( onDataChanged() ) );
    }

    emit endInsertRows();
    emit itemCountChanged( rowCount( QModelIndex() ) );
}


void
AlbumModel::onSourceAdded( const Hatchet::source_ptr& source )
{
    connect( source->dbCollection().data(), SIGNAL( changed() ), SLOT( onCollectionChanged() ), Qt::UniqueConnection );
}


void
AlbumModel::onCollectionChanged()
{
    addCollection( m_collection, true );
}


PlayableItem*
AlbumModel::findItem( const artist_ptr& artist ) const
{
    for ( int i = 0; i < rowCount( QModelIndex() ); i++ )
    {
        PlayableItem* item = itemFromIndex( index( i, 0, QModelIndex() ) );
        if ( !item->artist().isNull() && item->artist() == artist )
        {
            return item;
        }
    }

    return 0;
}


PlayableItem*
AlbumModel::findItem( const album_ptr& album ) const
{
    for ( int i = 0; i < rowCount( QModelIndex() ); i++ )
    {
        PlayableItem* item = itemFromIndex( index( i, 0, QModelIndex() ) );
        if ( !item->album().isNull() && item->album() == album )
        {
            return item;
        }
    }

    return 0;
}