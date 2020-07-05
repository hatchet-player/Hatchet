/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

/**
 * \class ArtistInfoWidget
 * \brief ViewPage, which displays top-hits, related artists and albums for an artist.
 *
 * This Hatchet ViewPage displays top-hits, related artists and known albums
 * for any given artist. It is our default ViewPage when showing an artist
 * via ViewManager.
 *
 */

#ifndef ARTISTINFOWIDGET_H
#define ARTISTINFOWIDGET_H

#include <QWidget>

#include "Typedefs.h"
#include "PlaylistInterface.h"
#include "ViewPage.h"
#include "utils/DpiScaler.h"

#include "DllMacro.h"

class QScrollArea;
class QStackedWidget;
class PlayableModel;
class PlaylistModel;
class BasicHeader;

namespace Ui
{
    class ArtistInfoWidget;
}

class MetaArtistInfoInterface;

class DLLEXPORT ArtistInfoWidget : public QWidget, public Hatchet::ViewPage, private HatchetUtils::DpiScaler
{
Q_OBJECT

public:
    ArtistInfoWidget( const Hatchet::artist_ptr& artist, QWidget* parent = 0 );
    ~ArtistInfoWidget();

    /** \brief Loads information for a given artist.
     *  \param artist The artist that you want to load information for.
     *
     *  Calling this method will make ArtistInfoWidget load information about
     *  an artist's top hits, related artists and all available albums. It is
     *  automatically called by the constructor, but you can use it to load
     *  another artist's information at any point.
     */
    void load( const Hatchet::artist_ptr& artist );

    Hatchet::artist_ptr artist() const { return m_artist; }

    virtual QWidget* widget() { return this; }
    virtual Hatchet::playlistinterface_ptr playlistInterface() const;

    virtual QString title() const { return m_title; }
    virtual QString description() const { return m_description; }
    virtual QString longDescription() const { return m_longDescription; }
    virtual QPixmap pixmap() const;

    virtual bool isTemporaryPage() const { return true; }

    virtual bool jumpToCurrentTrack();
    virtual bool isBeingPlayed() const;

signals:
    void longDescriptionChanged( const QString& description );
    void descriptionChanged( const QString& description );
    void pixmapChanged( const QPixmap& pixmap );

protected:
    void resizeEvent( QResizeEvent* event );
    void changeEvent( QEvent* e );
    bool eventFilter( QObject* obj, QEvent* event );

private slots:
    void onArtistImageUpdated();
    void onBiographyLoaded();

    void onAlbumsFound( const QList<Hatchet::album_ptr>& albums, Hatchet::ModelMode mode );
    void onTracksFound( const QList<Hatchet::query_ptr>& queries, Hatchet::ModelMode mode );
    void onSimilarArtistsLoaded();

    void onBiographyLinkClicked( const QUrl& url );
    void onAlbumsMoreClicked();
    void onTopHitsMoreClicked();
    void onPageClosed();

    void onMusicAnchorClicked();
    void onBioAnchorClicked();
    void onRelatedArtistsAnchorClicked();

    void onSliderValueChanged( int value );

private:
    Ui::ArtistInfoWidget *ui;

    QWidget* m_widget;
    BasicHeader* m_headerWidget;
    QScrollArea* m_area;

    Hatchet::artist_ptr m_artist;
    PlayableModel* m_relatedModel;
    PlayableModel* m_albumsModel;
    PlayableModel* m_topHitsModel;
    Hatchet::playlistinterface_ptr m_plInterface;

    QStackedWidget* m_stackedWidget;

    QString m_title;
    QString m_description;
    QString m_longDescription;
    QPixmap m_pixmap;

    friend class ::MetaArtistInfoInterface;
};

#endif // ARTISTINFOWIDGET_H
