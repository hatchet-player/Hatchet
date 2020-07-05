/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2014,      Teo Mrnjavac <teo@kde.org>
 *
 *   Hatchet is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hatchet is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hatchet. If not, see <http://www.gnu.org/licenses/>.
 */

#include "SplashWidget.h"

#include "utils/HatchetUtilsGui.h"
#include "utils/ImageRegistry.h"
#include "utils/DpiScaler.h"

#include <QBoxLayout>
#include <QLabel>
#ifdef Q_WS_X11
#include <QX11Info>
#endif

SplashWidget::SplashWidget()
    : QSplashScreen()
{
    //In 2014 there are still operating systems that cannot do transparency
    bool compositingWorks = true;
#if defined(Q_OS_WIN)
    compositingWorks = false;
#elif defined(Q_WS_X11) // QTBUG-41195: Qt5 lacks QX11Info::isCompositingManagerRunning()
    if ( !QX11Info::isCompositingManagerRunning() )
        compositingWorks = false;
#endif

    QString imagePath;
    if ( compositingWorks )
        imagePath = RESPATH "images/splash.svg";
    else
        imagePath = RESPATH "images/splash-unrounded.svg";

    QSize size( 600, 350 );

    setPixmap( ImageRegistry::instance()->pixmap( imagePath,
        HatchetUtils::DpiScaler::scaled( this, size ), HatchetUtils::Original ) );

    QFont font = this->font();

    font.setPointSize( HatchetUtils::defaultFontSize() - 1 );
    font.setBold( true );
    font.setFamily( "Roboto" );
    setFont( font );
}


void
SplashWidget::showMessage( const QString& message )
{
    QSplashScreen::showMessage( message + "\n", Qt::AlignBottom | Qt::AlignHCenter );
}
