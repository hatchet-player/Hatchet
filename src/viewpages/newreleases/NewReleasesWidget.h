/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012, Casey Link <unnamedrambler@gmail.com>
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2011, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef HATCHET_NEWRELEASESWIDGET_H
#define HATCHET_NEWRELEASESWIDGET_H

#include "../ViewPageDllMacro.h"
#include "ViewPagePlugin.h"
#include "ViewPageLazyLoader.h"

class AnimatedSpinner;
class PlayableModel;
class QSortFilterProxyModel;
class QStandardItemModel;
class QStandardItem;

namespace Ui
{
    class NewReleasesWidget;
}

namespace Hatchet
{
    class ChartDataLoader;
}

namespace Hatchet
{
namespace Widgets
{

/**
 * \class
 * \brief The hatchet page that shows new releases.
 */
class NewReleasesWidget : public QWidget
{
Q_OBJECT

public:
    NewReleasesWidget( QWidget* parent = 0 );
    ~NewReleasesWidget();

    Hatchet::playlistinterface_ptr playlistInterface() const;
    virtual bool isBeingPlayed() const;
    virtual bool jumpToCurrentTrack();

protected:
    void changeEvent( QEvent* e );

signals:
    void destroyed( QWidget* widget );

public slots:
    void fetchData();

private slots:
    void infoSystemInfo( Hatchet::InfoSystem::InfoRequestData requestData, QVariant output );
    void infoSystemFinished( QString target );
    void leftCrumbIndexChanged( QModelIndex );

    void newReleasesLoaded( Hatchet::ChartDataLoader*, const QList< Hatchet::album_ptr >& );

private:
    void setLeftViewAlbums( PlayableModel* albumModel );
    void setLeftViewTracks( PlaylistModel* trackModel );

    QStandardItem* parseNode( QStandardItem* parentItem, const QString &label, const QVariant &data );
    Ui::NewReleasesWidget *ui;
    Hatchet::playlistinterface_ptr m_playlistInterface;

    QStandardItemModel* m_crumbModelLeft;
    QSortFilterProxyModel* m_sortedProxy;

    // Load artist, album, and track objects in a thread
    // {Artist,Album,Track}::get() calls are all synchronous db calls
    // and we don't want to lock up out UI in case the db is busy (e.g. on startup)
    QThread* m_workerThread;
    QSet< Hatchet::ChartDataLoader* > m_workers;

    // Cache our model data
    QHash< QString, PlayableModel* > m_albumModels;
    QString m_queueItemToShow;
    QSet< QString > m_queuedFetches;
    AnimatedSpinner* m_spinner;
    bool m_loading;
};

const QString NEWRELEASES_VIEWPAGE_NAME = "newreleases";

class HATCHET_VIEWPAGE_EXPORT NewReleasesPage : public Hatchet::ViewPageLazyLoader< NewReleasesWidget >
{
    Q_OBJECT
    Q_INTERFACES( Hatchet::ViewPagePlugin )
    Q_PLUGIN_METADATA( IID "org.hatchet-player.Player.ViewPagePlugin" )

public:
    NewReleasesPage( QWidget* parent = 0 );
    virtual ~NewReleasesPage();

    const QString defaultName() Q_DECL_OVERRIDE { return NEWRELEASES_VIEWPAGE_NAME; }
    QString title() const Q_DECL_OVERRIDE { return tr( "New Releases" ); }
    QString description() const Q_DECL_OVERRIDE { return QString(); }

    const QString pixmapPath() const Q_DECL_OVERRIDE { return ( RESPATH "images/new-releases.svg" ); }

    int sortValue() Q_DECL_OVERRIDE { return 5; }
};


} // Widgets
} // Hatchet

#endif // HATCHET_NEWRELEASESWIDGET_H
