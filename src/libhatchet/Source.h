/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2013, Uwe L. Korn <uwelk@xhochy.com>
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

#ifndef SOURCE_H
#define SOURCE_H

#include <QObject>
#include <QSharedPointer>
#include <QVariantMap>

#include "accounts/AccountManager.h"
#include "collection/Collection.h"
#include "network/DBSyncConnectionState.h"
#include "utils/HatchetUtils.h"
#include "DllMacro.h"
#include "Typedefs.h"

class ControlConnection;
class DBSyncConnection;
class MusicScanner;

namespace Hatchet
{
class DatabaseCommand;
class DatabaseCommand_AddFiles;
class DatabaseCommand_DeleteFiles;
class DatabaseCommand_LoadAllSources;
class DatabaseCommand_LogPlayback;
class DatabaseCommand_SocialAction;
class DatabaseCommand_UpdateSearchIndex;

struct PlaybackLog;
class Resolver;
class SourcePrivate;

class DLLEXPORT Source : public QObject
{
Q_OBJECT

friend class ::DBSyncConnection;
friend class ::ControlConnection;
friend class DatabaseCommand_AddFiles;
friend class DatabaseCommand_DeleteFiles;
friend class DatabaseCommand_LoadAllSources;
friend class DatabaseCommand_LogPlayback;
friend class DatabaseCommand_SocialAction;
friend class ::MusicScanner;

public:
    explicit Source( int id, const QString& nodeId = QString() );
    virtual ~Source();

    bool isLocal() const;
    bool isOnline() const;

    QString nodeId() const;

    QString friendlyName() const;
    void setFriendlyName( const QString& fname );

    // fallback when the normal friendlyname from cache is not available
    // this is usually the jabber id or whatever was used when first connected
    QString dbFriendlyName() const;
    void setDbFriendlyName( const QString& dbFriendlyName );

    QPixmap avatar( HatchetUtils::ImageMode style = HatchetUtils::Original, const QSize& size = QSize(), bool defaultAvatarFallback = false );

    collection_ptr dbCollection() const;
    QList< Hatchet::collection_ptr > collections() const;
    void addCollection( const Hatchet::collection_ptr& c );
    void removeCollection( const Hatchet::collection_ptr& c );

    int id() const;
    ControlConnection* controlConnection() const;
    bool setControlConnection( ControlConnection* cc );

    const QSet< Hatchet::peerinfo_ptr > peerInfos() const;

    void scanningFinished( bool updateGUI );

    unsigned int trackCount() const;

    Hatchet::query_ptr currentTrack() const;
    QString textStatus() const;
    Hatchet::DBSyncConnectionState state() const;

    Hatchet::playlistinterface_ptr playlistInterface();

    QSharedPointer<QMutexLocker> acquireLock();

signals:
    void syncedWithDatabase();
    void synced();

    void online();
    void offline();

    void collectionAdded( const Hatchet::collection_ptr& collection );
    void collectionRemoved( const Hatchet::collection_ptr& collection );

    void stats( const QVariantMap& );

    void playbackStarted( const Hatchet::track_ptr& track );
    void playbackFinished( const Hatchet::track_ptr& track, const Hatchet::PlaybackLog& log );

    void stateChanged();
    void commandsFinished();

    void socialAttributesChanged( const QString& action );

    void latchedOn( const Hatchet::source_ptr& to );
    void latchedOff( const Hatchet::source_ptr& from );

public slots:
    void setStats( const QVariantMap& m );
    QString lastCmdGuid() const;

private slots:
    void setLastCmdGuid( const QString& guid );
    void dbLoaded( unsigned int id, const QString& fname );
    void updateIndexWhenSynced();

    void handleDisconnect( Hatchet::Accounts::Account*, Hatchet::Accounts::AccountManager::DisconnectReason reason );
    void setOffline();
    void setOnline( bool force = false );

    void onStateChanged( Hatchet::DBSyncConnectionState newstate, Hatchet::DBSyncConnectionState oldstate, const QString& info );

    void onPlaybackStarted( const Hatchet::track_ptr& track, unsigned int duration );
    void onPlaybackFinished( const Hatchet::track_ptr& track, const Hatchet::PlaybackLog& log );
    void trackTimerFired();

    void executeCommands();
    void addCommand( const dbcmd_ptr& command );

private:
    Q_DECLARE_PRIVATE( Source )
    SourcePrivate* d_ptr;

    static bool friendlyNamesLessThan( const QString& first, const QString& second ); //lessThan for sorting
    QString prettyName( const QString& name ) const;

    void updateTracks();
    void reportSocialAttributesChanged( DatabaseCommand_SocialAction* action );
};

} //ns

#endif // SOURCE_H
