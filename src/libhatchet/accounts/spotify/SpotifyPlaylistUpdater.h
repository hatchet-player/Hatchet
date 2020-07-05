/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2012, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2012, Hugo Lindström <hugolm84@gmail.com>
 *   Copyright 2013, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef SPOTIFYPLAYLISTUPDATER_H
#define SPOTIFYPLAYLISTUPDATER_H

#include "playlist/PlaylistUpdaterInterface.h"
#include "utils/Closure.h"
#include "DllMacro.h"
#include "Typedefs.h"

#include <QQueue>
#include <QVariant>

namespace Hatchet {
    namespace Accounts {
        class SpotifyAccount;
    }
}

class DLLEXPORT SpotifyPlaylistUpdater : public Hatchet::PlaylistUpdaterInterface
{
    Q_OBJECT

    friend class Hatchet::Accounts::SpotifyAccount;
public:
    SpotifyPlaylistUpdater( Hatchet::Accounts::SpotifyAccount* acct, const QString& revid, const QString& spotifyId, const Hatchet::playlist_ptr& pl );

    virtual ~SpotifyPlaylistUpdater();

    virtual QString type() const;
    virtual void updateNow() {}

    virtual QWidget* configurationWidget() const { return 0; }
    virtual QPixmap typeIcon() const;

    bool sync() const;
    void setSync( bool sync );

    bool subscribed() const;
    // actually change the subscribed value in spotify
    void setSubscribed( bool subscribed );
    // Just set the subscribed flag
    void setSubscribedStatus( bool subscribed );
    bool canSubscribe() const;
    void setCanSubscribe( bool canSub );
    void setSubscribers( int numSubscribers );
    int subscribers() const { return m_subscribers; }
    // Collaborative actions

    void setOwner( bool owner );
    bool owner() const;
    bool collaborative() const;
    void setCollaborative( bool collaborative );

    QString spotifyId() const { return m_spotifyId; }

    virtual bool hasCustomDeleter() const { return true; }
    virtual Hatchet::PlaylistDeleteQuestions deleteQuestions() const;
    virtual void setQuestionResults( const QMap< int, bool > results );

    void remove( bool askToDeletePlaylist = true );

public slots:
    /// Spotify callbacks when we are directly instructed from the resolver
    void spotifyTracksAdded( const QVariantList& tracks, const QString& startPosId, const QString& newRev, const QString& oldRev );
    void spotifyTracksRemoved( const QVariantList& tracks, const QString& newRev, const QString& oldRev );
    void spotifyTracksMoved( const QVariantList& tracks, const QString& newStartPos, const QString& newRev, const QString& oldRev );
    void spotifyPlaylistRenamed( const QString& title, const QString& newRev, const QString& oldRev  );

    void hatchetTracksInserted( const QList<Hatchet::plentry_ptr>& ,int );
    void hatchetTracksRemoved( const QList<Hatchet::query_ptr>& );
    void hatchetTracksMoved( const QList<Hatchet::plentry_ptr>& ,int );
    void hatchetPlaylistRenamed( const QString&, const QString& );

private slots:
    // SpotifyResolver message handlers, all take msgtype, msg as argument
    void onTracksInsertedReturn( const QString& msgType, const QVariantMap& msg, const QVariant& extraData );
    void onTracksRemovedReturn( const QString& msgType, const QVariantMap& msg, const QVariant& extraData );
    void onTracksMovedReturn( const QString& msgType, const QVariantMap& msg, const QVariant& extraData );

    void unsyncOrDelete( bool toDelete );

    void playlistRevisionLoaded();

private:
    void init();
    void saveToSettings();

    /// Finds the nearest spotify id from pos to the beginning of the playlist
    QString nearestSpotifyTrack( const QList< Hatchet::plentry_ptr >& entries, int pos );
    QVariantList plentryToVariant( const QList< Hatchet::plentry_ptr >& entries );

    static QVariantList queriesToVariant( const QList< Hatchet::query_ptr >& queries );
    static QVariant queryToVariant( const Hatchet::query_ptr& query );
    static QList< Hatchet::query_ptr > variantToQueries( const QVariantList& list );

    QPointer<Hatchet::Accounts::SpotifyAccount> m_spotify;
    QString m_latestRev, m_spotifyId;
    QList< Hatchet::plentry_ptr > m_waitingForIds;

    bool m_blockUpdatesForNextRevision;
    bool m_sync;
    bool m_subscribed;
    bool m_canSubscribe;
    bool m_isOwner;
    bool m_collaborative;
    int m_subscribers;

    QQueue<_detail::Closure*> m_queuedOps;
    static QPixmap* s_typePixmap;
};


class DLLEXPORT SpotifyUpdaterFactory : public Hatchet::PlaylistUpdaterFactory
{
public:
    SpotifyUpdaterFactory()  {}

    virtual Hatchet::PlaylistUpdaterInterface* create( const Hatchet::playlist_ptr& pl, const QVariantHash& settings );
    virtual QString type() const { return "spotify"; }

private:
    QPointer<Hatchet::Accounts::SpotifyAccount> m_account;
};

#endif // SPOTIFYPLAYLISTUPDATER_H
