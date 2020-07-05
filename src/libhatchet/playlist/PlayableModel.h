/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2011       Leo Franchi <lfranchi@kde.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
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
#ifndef PLAYABLEMODEL_H
#define PLAYABLEMODEL_H

#include "DllMacro.h"
#include "PlaybackLog.h"
#include "Typedefs.h"

#include <QAbstractItemModel>

class QMetaData;

class PlayableItem;
class PlayableModelPrivate;

class DLLEXPORT PlayableModel : public QAbstractItemModel
{
Q_OBJECT

public:
    enum Columns
    {
        Artist = 0,
        Track = 1,
        Composer = 2,
        Album = 3,
        Download = 4,
        AlbumPos = 5,
        Duration = 6,
        Bitrate = 7,
        Age = 8,
        Year = 9,
        Filesize = 10,
        Origin = 11,
        Score = 12,
        Name = 13,
    };

    enum PlayableRoles
    {
        ArtistRole = Qt::UserRole,
        TrackRole,
        ComposerRole,
        AlbumRole,
        DownloadRole,
        AlbumPosRole,
        DurationRole,
        BitrateRole,
        AgeRole,
        YearRole,
        FilesizeRole,
        OriginRole,
        ScoreRole,
        NameRole,
        CoverIDRole,
        IsPlayingRole
    };

    explicit PlayableModel( QObject* parent = 0, bool loading = true );
    virtual ~PlayableModel();

    virtual QString guid() const { return QString(); }

    virtual QModelIndex index( int row, int column, const QModelIndex& parent ) const;
    virtual QModelIndex parent( const QModelIndex& child ) const;

    virtual bool isReadOnly() const;
    virtual void setReadOnly( bool b );
    virtual bool isLoading() const;

    virtual QString title() const;
    virtual void setTitle( const QString& title );
    virtual QString description() const;
    virtual void setDescription( const QString& description );
    virtual QPixmap icon() const;
    virtual void setIcon( const QPixmap& pixmap );


    // HACK: we need to set column 0 editable for DropDownButton in TrackView
    void setAllColumnsEditable( bool editable );
    bool areAllColumnsEditable() const;

    virtual int trackCount() const;
    virtual int itemCount() const;

    virtual int rowCount( const QModelIndex& parent ) const;
    virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual bool hasChildren( const QModelIndex& parent ) const;

    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
    virtual QVariant headerData( int section, Qt::Orientation orientation, int role ) const;

    virtual QVariant artistData( const Hatchet::artist_ptr& artist, int role = Qt::DisplayRole ) const;
    virtual QVariant albumData( const Hatchet::album_ptr& album, int role = Qt::DisplayRole ) const;
    virtual QVariant queryData( const Hatchet::query_ptr&, int column, int role = Qt::DisplayRole ) const;

    virtual QMimeData* mimeData( const QModelIndexList& indexes ) const;
    virtual QStringList mimeTypes() const;
    virtual Qt::DropActions supportedDropActions() const;
    virtual Qt::ItemFlags flags( const QModelIndex& index ) const;

    virtual QPersistentModelIndex currentItem();
    virtual Hatchet::QID currentItemUuid();

    virtual Hatchet::PlaylistModes::RepeatMode repeatMode() const;
    virtual bool shuffled() const { return false; }

    virtual void ensureResolved( const QModelIndex& parent = QModelIndex() );

    virtual PlayableItem* itemFromIndex( const QModelIndex& index ) const;
    virtual PlayableItem* itemFromQuery( const Hatchet::query_ptr& query, const QModelIndex& parent = QModelIndex() ) const;
    virtual PlayableItem* itemFromResult( const Hatchet::result_ptr& result, const QModelIndex& parent = QModelIndex() ) const;
    virtual QModelIndex indexFromSource( const Hatchet::source_ptr& source ) const;

    /// Returns a flat list of all tracks in this model
    QList< Hatchet::query_ptr > queries() const;

    void startLoading();
    void finishLoading();

signals:
    void repeatModeChanged( Hatchet::PlaylistModes::RepeatMode mode );
    void shuffleModeChanged( bool enabled );

    void itemCountChanged( unsigned int items );

    void loadingStarted();
    void loadingFinished();

    void indexResolved( const QModelIndex& index );
    void indexPlayable( const QModelIndex& index );

    void changed();
    void currentIndexChanged( const QModelIndex& newIndex, const QModelIndex& oldIndex );

    void expandRequest( const QPersistentModelIndex& index );
    void selectRequest( const QPersistentModelIndex& index );

public slots:
    virtual void setCurrentIndex( const QModelIndex& index );

    virtual void clear();

    virtual void appendTracks( const QList< Hatchet::track_ptr >& tracks, const QList< Hatchet::PlaybackLog >& logs = QList< Hatchet::PlaybackLog >() );
    virtual void appendQueries( const QList< Hatchet::query_ptr >& queries );
    virtual void appendArtists( const QList< Hatchet::artist_ptr >& artists );
    virtual void appendAlbums( const QList< Hatchet::album_ptr >& albums );
    virtual void appendAlbums( const Hatchet::collection_ptr& collection );
    virtual void appendQuery( const Hatchet::query_ptr& query );
    virtual void appendArtist( const Hatchet::artist_ptr& artist );
    virtual void appendAlbum( const Hatchet::album_ptr& album );
    virtual void appendTracks( const Hatchet::collection_ptr& collection );

    virtual void insertQueries( const QList< Hatchet::query_ptr >& queries, int row = 0, const QList< Hatchet::PlaybackLog >& logs = QList< Hatchet::PlaybackLog >(), const QModelIndex& parent = QModelIndex() );
    virtual void insertArtists( const QList< Hatchet::artist_ptr >& artists, int row = 0 );
    virtual void insertAlbums( const QList< Hatchet::album_ptr >& albums, int row = 0 );
    virtual void insertAlbums( const Hatchet::collection_ptr& collection, int row = 0 );
    virtual void insertQuery( const Hatchet::query_ptr& query, int row = 0, const Hatchet::PlaybackLog& log = Hatchet::PlaybackLog(), const QModelIndex& parent = QModelIndex() );
    virtual void insertArtist( const Hatchet::artist_ptr& artist, int row = 0 );
    virtual void insertAlbum( const Hatchet::album_ptr& album, int row = 0 );
    virtual void insertTracks( const Hatchet::collection_ptr& collection, int row = 0 );

    virtual bool removeRows( int row, int count, const QModelIndex& parent = QModelIndex() );
    virtual void remove( int row, bool moreToCome = false, const QModelIndex& parent = QModelIndex() );
    virtual void removeIndex( const QModelIndex& index, bool moreToCome = false );
    virtual void removeIndexes( const QList<QModelIndex>& indexes );
    virtual void removeIndexes( const QList<QPersistentModelIndex>& indexes );

    virtual void setRepeatMode( Hatchet::PlaylistModes::RepeatMode /*mode*/ ) {}
    virtual void setShuffled( bool /*shuffled*/ ) {}

protected:
    QScopedPointer<PlayableModelPrivate> d_ptr;
    PlayableModel( QObject* parent, PlayableModelPrivate* d );

    PlayableItem* rootItem() const;
    QModelIndex createIndex( int row, int column, PlayableItem* item = 0 ) const;

private slots:
    void onDataChanged();

    void onQueryBecamePlayable( bool playable );
    void onQueryResolved( bool hasResults );

    void onPlaybackStarted( const Hatchet::result_ptr result );
    void onPlaybackStopped();

private:
    void init();
    template <typename T>
    void insertInternal( const QList< T >& items, int row, const QList< Hatchet::PlaybackLog >& logs = QList< Hatchet::PlaybackLog >(), const QModelIndex& parent = QModelIndex() );

    QString scoreText( float score ) const;
    Qt::Alignment columnAlignment( int column ) const;

    Q_DECLARE_PRIVATE( PlayableModel )
};

#endif // PLAYABLEMODEL_H
