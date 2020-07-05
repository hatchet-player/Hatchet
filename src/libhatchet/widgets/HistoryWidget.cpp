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

#include "HistoryWidget.h"

#include "ViewManager.h"
#include "SourceList.h"
#include "HatchetSettings.h"
#include "MetaPlaylistInterface.h"

#include "playlist/RecentlyPlayedModel.h"
#include "playlist/ContextView.h"
#include "playlist/TrackView.h"
#include "utils/HatchetStyle.h"
#include "utils/HatchetUtilsGui.h"
#include "utils/Logger.h"

#include <QCalendarWidget>
#include <QDateEdit>
#include <QLabel>
#include <QHBoxLayout>

using namespace Hatchet;

HistoryWidget::HistoryWidget( const source_ptr& source, QWidget* parent )
: PlaylistViewPage( parent )
{
    setPixmap( HatchetUtils::defaultPixmap( HatchetUtils::RecentlyPlayed ) );

    m_model = new RecentlyPlayedModel( this );
    m_model->setTitle( tr( "Recently Played Tracks" ) );

    if ( source->isLocal() )
        m_model->setDescription( tr( "Your recently played tracks" ) );
    else
        m_model->setDescription( tr( "%1's recently played tracks" ).arg( source->friendlyName() ) );

    view()->trackView()->setIndentation( 0 );
    view()->trackView()->setUniformRowHeights( false );

    view()->trackView()->setPlayableModel( m_model );
    view()->setEmptyTip( tr( "Sorry, we could not find any recent plays!" ) );
    m_model->setSource( source );

    view()->setGuid( QString( "recentplays/%1" ).arg( source->nodeId() ) );
}


HistoryWidget::~HistoryWidget()
{
}


void
HistoryWidget::onDateClicked( const QDate& date )
{
/*    QDateEdit* cw = qobject_cast< QDateEdit* >( sender() );
    if ( cw == m_calendarFrom && date > m_calendarTo->date())
    {
        m_calendarTo->setDate( date );
    }
    if ( cw == m_calendarTo && date < m_calendarFrom->date())
    {
        m_calendarFrom->setDate( date );
    }

    m_model->setLimit( 0 );
    m_model->setDateFrom( m_calendarFrom->date() );
    m_model->setDateTo( m_calendarTo->date() );*/
}
