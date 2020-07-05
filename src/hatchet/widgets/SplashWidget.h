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

#ifndef SPLASHWIDGET_H
#define SPLASHWIDGET_H

#include <QSplashScreen>

class SplashWidget : public QSplashScreen
{
    Q_OBJECT
public:
    explicit SplashWidget();

    void showMessage( const QString& message );

};

#endif // SPLASHWIDGET_H
