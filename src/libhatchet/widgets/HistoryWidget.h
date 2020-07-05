/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
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

#ifndef HISTORY_WIDGET_H
#define HISTORY_WIDGET_H

#include "viewpages/PlaylistViewPage.h"
#include "Query.h"
#include "Source.h"
#include "DllMacro.h"

class QCalendarWidget;
class QDateEdit;
class RecentlyPlayedModel;

class DLLEXPORT HistoryWidget : public PlaylistViewPage
{
Q_OBJECT

public:
    explicit HistoryWidget( const Hatchet::source_ptr& source, QWidget* parent = 0 );
    virtual ~HistoryWidget();

signals:

private slots:
    void onDateClicked( const QDate& date );

private:
    RecentlyPlayedModel* m_model;

/*    QCalendarWidget* m_calendarFrom;
    QCalendarWidget* m_calendarTo;*/
    QDateEdit* m_calendarFrom;
    QDateEdit* m_calendarTo;
};

#endif // HISTORY_WIDGET_H
