/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2013,      Teo Mrnjavac <teo@kde.org>
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
#ifndef TRACK_H
#define TRACK_H

#include "DllMacro.h"
#include "PlaybackLog.h"
#include "SocialAction.h"
#include "Typedefs.h"

#include <QList>
#include <QVariant>


namespace Hatchet
{

class DatabaseCommand_LoadInboxEntries;
class TrackPrivate;

class DLLEXPORT Track : public QObject
{
Q_OBJECT

friend class Pipeline;
friend class DatabaseCommand_LoadInboxEntries; // for setAllSocialActions

public:
    enum DescriptionMode
    { Detailed = 0, Short = 1 };

    static track_ptr get( const QString& artist, const QString& track, const QString& album = QString(), const QString& albumArtist = QString(), int duration = 0, const QString& composer = QString(), unsigned int albumpos = 0, unsigned int discnumber = 0 );
    static track_ptr get( unsigned int id, const QString& artist, const QString& track, const QString& album, const QString& albumArtist, int duration, const QString& composer, unsigned int albumpos, unsigned int discnumber );

    virtual ~Track();

    void setArtist( const QString& artist );
    void setAlbum( const QString& album );
    void setTrack( const QString& track );

    void setAlbumPos( unsigned int albumpos );
    // void setDuration( int duration ) { m_duration = duration; }
    // void setDiscNumber( unsigned int discnumber ) { m_discnumber = discnumber; }
    // void setComposer( const QString& composer ) { m_composer = composer; updateSortNames(); }

    bool equals( const Hatchet::track_ptr& other, bool ignoreCase = false ) const;

    QVariant toVariant() const;
    QString toString() const;
    Hatchet::query_ptr toQuery();

    const QString& composerSortname() const;
    const QString& albumSortname() const;
    const QString& artistSortname() const;
    const QString& trackSortname() const;

    QString artist() const;
    QString albumArtist() const;
    QString track() const;
    QString composer() const;
    QString album() const;
    int duration() const;
    int year() const;
    unsigned int albumpos() const;
    unsigned int discnumber() const;

    Hatchet::artist_ptr artistPtr() const;
    Hatchet::artist_ptr albumArtistPtr() const;
    Hatchet::album_ptr albumPtr() const;
    Hatchet::artist_ptr composerPtr() const;

    QPixmap cover( const QSize& size, bool forceLoad = true ) const;
    bool coverLoaded() const;

    void setLoved( bool loved, bool postToInfoSystem = true );
    bool loved();

    void share( const Hatchet::source_ptr& source );

    void loadAttributes();
    QVariantMap attributes() const;
    void setAttributes( const QVariantMap& map );

    void loadStats();
    QList< Hatchet::PlaybackLog > playbackHistory( const Hatchet::source_ptr& source = Hatchet::source_ptr() ) const;
    unsigned int playbackCount( const Hatchet::source_ptr& source = Hatchet::source_ptr() );

    unsigned int chartPosition() const;
    unsigned int chartCount() const;

    void loadSocialActions( bool force = false );
    QList< Hatchet::SocialAction > allSocialActions() const;
    QList< Hatchet::SocialAction > socialActions( const QString& actionName, const QVariant& value = QVariant(), bool filterDupeSourceNames = false );
    QString socialActionDescription( const QString& actionName, DescriptionMode mode ) const;

    QList<Hatchet::query_ptr> similarTracks() const;
    QStringList lyrics() const;

    unsigned int trackId() const;

    QWeakPointer< Hatchet::Track > weakRef();
    void setWeakRef( QWeakPointer< Hatchet::Track > weakRef );

    void startPlaying();
    void finishPlaying( int timeElapsed );

    void markAsListened();
    bool isListened() const;

signals:
    void coverChanged();
    void socialActionsLoaded();
    void attributesLoaded();
    void statsLoaded();
    void similarTracksLoaded();
    void lyricsLoaded();

    void updated();

public slots:
    void deleteLater();

protected:
    QScopedPointer<TrackPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE( Track )
    explicit Track( unsigned int id, const QString& artist, const QString& track, const QString& album, const QString& albumArtist, int duration, const QString& composer, unsigned int albumpos, unsigned int discnumber );
    explicit Track( const QString& artist, const QString& track, const QString& album, const QString& albumArtist, int duration, const QString& composer, unsigned int albumpos, unsigned int discnumber );

    void init();

    void updateSortNames();

    void setAllSocialActions( const QList< SocialAction >& socialActions );

    static QHash< QString, track_wptr > s_tracksByName;
};

} // namespace Hatchet

Q_DECLARE_METATYPE( Hatchet::track_ptr )

#endif // TRACK_H
