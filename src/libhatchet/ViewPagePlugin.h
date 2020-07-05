/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013,    Dominik Schmidt <domme@tomahawk-player.org>
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

#ifndef VIEWPAGEPLUGIN_H
#define VIEWPAGEPLUGIN_H

#include "ViewPage.h"

#include "DllMacro.h"

namespace Hatchet
{


class DLLEXPORT ViewPagePlugin : public QObject, public ViewPage
{
Q_OBJECT

public:
    ViewPagePlugin( QObject* parent = 0 );
    virtual ~ViewPagePlugin();

    virtual const QString defaultName() = 0;
    virtual int sortValue();

    // pixmap() by default returns a scaled instance of pixmapPath
    virtual QPixmap pixmap() const;
    virtual const QString pixmapPath() const;

signals:
    void nameChanged( const QString& );
    void descriptionChanged( const QString& );
    void descriptionChanged( const Hatchet::artist_ptr& artist );
    void descriptionChanged( const Hatchet::album_ptr& album );
    void longDescriptionChanged( const QString& );
    void pixmapChanged( const QPixmap& );
    void destroyed( QWidget* widget );
};


} // ns

Q_DECLARE_INTERFACE( Hatchet::ViewPagePlugin, "hatchet.ViewPage/1.0" )

#endif //VIEWPAGEPLUGIN_H
