/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2013,      Teo Mrnjavac <teo@kde.org>
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

/*
    The collection  - acts as container for someones music library
    load() -> async populate by calling addArtists etc,
    then finishedLoading() is emitted.
    then use artists() etc to get the data.
*/

#ifndef HATCHET_COLLECTION_H
#define HATCHET_COLLECTION_H

#include "Typedefs.h"
#include "Playlist.h"
#include "playlist/dynamic/DynamicPlaylist.h"
#include "collection/ArtistsRequest.h"
#include "collection/AlbumsRequest.h"
#include "collection/TracksRequest.h"
#include "../resolvers/Resolver.h"

#include "DllMacro.h"

#include <QHash>
#include <QList>
#include <QSharedPointer>
#include <QSet>


namespace Hatchet
{

class DLLEXPORT Collection : public Resolver
{
Q_OBJECT

public:
    Collection( const source_ptr& source, const QString& name, QObject* parent = 0 );
    virtual ~Collection();

    void setWeakRef( const collection_wptr& weakRef );
    collection_wptr weakRef() const;

    enum BrowseCapability
    {
        CapabilityBrowseNull    = 0x0,
        CapabilityBrowseArtists = 0x1,
        CapabilityBrowseAlbums  = 0x2,
        CapabilityBrowseTracks  = 0x4
    };

    QSet< BrowseCapability > browseCapabilities() const;

    enum BackendType
    {
        NullCollectionType = 0,
        DatabaseCollectionType, //talks to a database, incl. LocalCollection
        ScriptCollectionType    //performs operations through a resolver
    };

    virtual QString name() const override;
    virtual QString prettyName() const;
    virtual QString description() const;
    virtual QString itemName() const;
    virtual BackendType backendType() const { return NullCollectionType; }
    virtual QPixmap icon( const QSize& size ) const override;
    virtual QPixmap bigIcon() const; //for the ViewPage header

    virtual bool isOnline() const = 0;
    virtual bool isLocal() const;

    virtual void loadPlaylists();
    virtual void loadAutoPlaylists();
    virtual void loadStations();

    virtual Hatchet::playlist_ptr playlist( const QString& guid );
    virtual Hatchet::dynplaylist_ptr autoPlaylist( const QString& guid );
    virtual Hatchet::dynplaylist_ptr station( const QString& guid );

    virtual void addPlaylist( const Hatchet::playlist_ptr& p );
    virtual void deletePlaylist( const Hatchet::playlist_ptr& p );

    virtual void addAutoPlaylist( const Hatchet::dynplaylist_ptr& p );
    virtual void deleteAutoPlaylist( const Hatchet::dynplaylist_ptr& p );

    virtual void addStation( const Hatchet::dynplaylist_ptr& s );
    virtual void deleteStation( const Hatchet::dynplaylist_ptr& s );

    virtual QList< Hatchet::playlist_ptr > playlists() { return m_playlists.values(); }
    virtual QList< Hatchet::dynplaylist_ptr > autoPlaylists() { return m_autoplaylists.values(); }
    virtual QList< Hatchet::dynplaylist_ptr > stations() { return m_stations.values(); }

    // Async requests. Emit artists/albums/tracksResult in subclasses when finished.
    virtual Hatchet::ArtistsRequest* requestArtists() = 0;
    virtual Hatchet::AlbumsRequest* requestAlbums( const Hatchet::artist_ptr& artist ) = 0;
    virtual Hatchet::TracksRequest* requestTracks( const Hatchet::album_ptr& album ) = 0;

    unsigned int lastmodified() const { return m_lastmodified; }

    virtual int trackCount() const;

signals:
    void tracksAdded( const QList<unsigned int>& fileids );
    void tracksRemoved( const QList<unsigned int>& fileids );

    void playlistsAdded( const QList<Hatchet::playlist_ptr>& );
    void playlistsDeleted( const QList<Hatchet::playlist_ptr>& );

    void autoPlaylistsAdded( const QList<Hatchet::dynplaylist_ptr>& );
    void autoPlaylistsDeleted( const QList<Hatchet::dynplaylist_ptr>& );

    void stationsAdded( const QList<Hatchet::dynplaylist_ptr>& );
    void stationsDeleted( const QList<Hatchet::dynplaylist_ptr>& );

    void changed();

    void online();
    void offline();

public slots:
    void setPlaylists( const QList<Hatchet::playlist_ptr>& plists );
    void setAutoPlaylists( const QList< Hatchet::dynplaylist_ptr >& autoplists );
    void setStations( const QList< Hatchet::dynplaylist_ptr >& stations );

    void setTracks( const QList<unsigned int>& fileids );
    void delTracks( const QList<unsigned int>& fileids );

protected:
    source_ptr source() const;

private slots:
    void onSynced();
    void doLoadPlaylistUpdater( const playlist_ptr& p );


protected:
    QString m_name;
    unsigned int m_lastmodified; // unix time of last change to collection
    QSet< BrowseCapability > m_browseCapabilities;

private:
    bool m_changed;

    collection_wptr m_ownRef;
    source_ptr m_source;

    QHash< QString, Hatchet::playlist_ptr > m_playlists;
    QHash< QString, Hatchet::dynplaylist_ptr > m_autoplaylists;
    QHash< QString, Hatchet::dynplaylist_ptr > m_stations;

    // HACK see line 99 in the dbcmd for why we need this for backwards-compatibility
    void moveAutoToStation( const QString& guid );
    void moveStationToAuto( const QString& guid );
    friend class DatabaseCommand_SetDynamicPlaylistRevision;
};

} // ns

inline uint qHash( const QSharedPointer<Hatchet::Collection>& key )
{
    return qHash( (void *)key.data() );
}

#endif // HATCHET_COLLECTION_H
