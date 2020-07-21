/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2015, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2014, Dominik Schmidt <domme@tomahawk-player.org>
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

#include "WebPopup.h"

#include <QDesktopServices>


bool
ExternalBrowserWebPage::acceptNavigationRequest( QWebEnginePage*, const QNetworkRequest& request, NavigationType )
{
    QDesktopServices::openUrl( request.url() );
    return false;
}


WebPopup::WebPopup( const QUrl& url, const QSize& size )
    : QWebEngineView( 0 )
{
    setAttribute( Qt::WA_DeleteOnClose, true );
    /* QT5.15 DISABLE
    settings()->setAttribute( QWebEngineSettings::DeveloperExtrasEnabled, true ); TODO - fix/remove
    settings()->setAttribute( QWebEngineSettings::JavascriptCanCloseWindows, true ); TODO - fix/remove
    page()->setScrollBarPolicy( Qt::Vertical, Qt::ScrollBarAsNeeded );
    page()->setScrollBarPolicy( Qt::Horizontal, Qt::ScrollBarAsNeeded );
    */
    connect( page(), SIGNAL( windowCloseRequested() ), SLOT( close() ) );

    if ( !size.isEmpty() )
    {
        resize( size );
    }

    load( url );
    show();
}


QWebEngineView*
WebPopup::createWindow( QWebEnginePage::WebWindowType )
{
    QWebEngineView* fakeWindow = new QWebEngineView();
    fakeWindow->setPage( new ExternalBrowserWebPage( fakeWindow ) );
    fakeWindow->deleteLater();
    return fakeWindow;
}
