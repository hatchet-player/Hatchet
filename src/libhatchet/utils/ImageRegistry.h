/*
 *   Copyright 2012, Christian Muehlhaeuser <muesli@tomahawk-player.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef IMAGE_REGISTRY_H
#define IMAGE_REGISTRY_H

#include <QPixmap>

#include "utils/HatchetUtilsGui.h"
#include "DllMacro.h"

class DLLEXPORT ImageRegistry
{
public:
    static ImageRegistry* instance();

    explicit ImageRegistry();

    QIcon icon( const QString& image, HatchetUtils::ImageMode mode = HatchetUtils::Original );
    QPixmap pixmap( const QString& image, const QSize& size, HatchetUtils::ImageMode mode = HatchetUtils::Original, float opacity = 1.0, QColor tint = QColor( 0, 0, 0, 0 ) );

private:
    qint64 cacheKey( const QSize& size, float opacity, QColor tint );
    void putInCache( const QString& image, const QSize& size, HatchetUtils::ImageMode mode, float opacity, const QPixmap& pixmap, QColor tint );

    static ImageRegistry* s_instance;
};

#endif // IMAGE_REGISTRY_H
