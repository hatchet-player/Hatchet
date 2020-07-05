/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
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

#ifndef NETWORKACTIVITYWIDGET_H
#define NETWORKACTIVITYWIDGET_H

#include "ViewPage.h"

#include "../ViewPageDllMacro.h"

class AnimatedSpinner;
class PlaylistModel;
class QModelIndex;
class QStandardItemModel;
class QSortFilterProxyModel;
namespace Ui
{
    class NetworkActivityWidget;
}

namespace Hatchet
{
namespace Widgets
{

class NetworkActivityWidgetPrivate;

class HATCHET_VIEWPAGE_EXPORT NetworkActivityWidget : public QWidget
{
    Q_OBJECT
public:
    enum ViewType
    {
        WeekChart = 1,
        MonthChart = 2,
        YearChart = 3,
        OverallChart = 4,
        TopLoved = 5,
        RecentlyLoved = 6
    };

    NetworkActivityWidget(QWidget* parent = 0);
    ~NetworkActivityWidget();

    static const uint numberOfHotPlaylists = 3;
    static const uint numberOfTrendingArtists = 3;
    static const uint numberOfTrendingTracks = 3;
    static const uint numberOfNetworkChartEntries = 20;
    
    // ViewPageWidget interface
    virtual Hatchet::playlistinterface_ptr playlistInterface() const;
    virtual bool isBeingPlayed() const;
    virtual bool jumpToCurrentTrack();

protected:
    QScopedPointer<NetworkActivityWidgetPrivate> d_ptr;

private slots:
    void weeklyCharts( const QList<Hatchet::track_ptr>& );
    void monthlyCharts( const QList<Hatchet::track_ptr>& );
    void yearlyCharts( const QList<Hatchet::track_ptr>& );
    void overallCharts( const QList<Hatchet::track_ptr>& );

    void hotPlaylists( const QList<Hatchet::playlist_ptr>& playlists );
    void trendingArtists( const QList< Hatchet::artist_ptr >& artists );
    void trendingTracks( const QList< Hatchet::track_ptr >& tracks );

    void leftCrumbIndexChanged( const QModelIndex& );
    void onPlaylistActivated( const QModelIndex& );

private:
    void fetchWeekCharts();
    void fetchMonthCharts();
    void fetchYearCharts();
    void fetchOverallCharts();
    void fetchTopLoved();
    void fetchRecentlyLoved();

    void showWeekCharts();
    void showMonthCharts();
    void showYearCharts();
    void showOverallCharts();
    void showTopLoved();
    void showRecentlyLoved();

    Q_DECLARE_PRIVATE( NetworkActivityWidget )
};

} // Widgets

} // Hatchet

#endif // NETWORKACTIVITYWIDGET_H
