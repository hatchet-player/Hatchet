/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include "PlaylistViewPage.h"

#include <QRadioButton>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "widgets/FilterHeader.h"
#include "playlist/ContextView.h"
#include "playlist/TrackView.h"
#include "playlist/PlayableProxyModelPlaylistInterface.h"
#include "utils/HatchetUtilsGui.h"
#include "utils/ImageRegistry.h"
#include "utils/Logger.h"

using namespace Hatchet;


PlaylistViewPage::PlaylistViewPage( QWidget* parent, QWidget* extraHeader )
    : QWidget( parent )
    , m_header( new FilterHeader( this ) )
    , m_view( new ContextView( this ) )
    , m_temporary( false )
{
    m_header->setBackground( ImageRegistry::instance()->pixmap( RESPATH "images/playlist_background.png", QSize( 0, 0 ) ) );

    setLayout( new QVBoxLayout() );

    layout()->addWidget( m_header );
    if ( extraHeader )
        layout()->addWidget( extraHeader );
    layout()->addWidget( m_view );

    connect( m_header, SIGNAL( filterTextChanged( QString ) ), SLOT( setFilter( QString ) ) );
    connect( m_view, SIGNAL( modelChanged() ), SLOT( onModelChanged() ) );

    HatchetUtils::unmarginLayout( layout() );
    HatchetUtils::fixMargins( this );
}


PlaylistViewPage::~PlaylistViewPage()
{
    tDebug() << Q_FUNC_INFO;
}


Hatchet::playlistinterface_ptr
PlaylistViewPage::playlistInterface() const
{
    return m_view->playlistInterface();
}


QString
PlaylistViewPage::title() const
{
    return m_view->trackView()->title();
}


QString
PlaylistViewPage::description() const
{
    return m_view->trackView()->description();
}


QPixmap
PlaylistViewPage::pixmap() const
{
    return m_pixmap;
}


bool
PlaylistViewPage::jumpToCurrentTrack()
{
    return m_view->jumpToCurrentTrack();
}


bool
PlaylistViewPage::setFilter( const QString& pattern )
{
    ViewPage::setFilter( pattern );

    return m_view->setFilter( pattern );
}


void
PlaylistViewPage::setPixmap( const QPixmap& pixmap )
{
    m_pixmap = pixmap;
    m_header->setPixmap( pixmap );
}


void
PlaylistViewPage::onModelChanged()
{
    m_header->setCaption( m_view->trackView()->model()->title() );
    m_header->setDescription( m_view->trackView()->model()->description() );
}


void
PlaylistViewPage::onWidgetDestroyed( QWidget* widget )
{
    Q_UNUSED( widget );
    emit destroyed( this );
}


bool
PlaylistViewPage::isTemporaryPage() const
{
    return m_temporary;
}


void
PlaylistViewPage::setTemporaryPage( bool b )
{
    m_temporary = b;
}


bool
PlaylistViewPage::isBeingPlayed() const
{
    return m_view->isBeingPlayed();
}


ContextView*
PlaylistViewPage::view() const
{
    return m_view;
}
