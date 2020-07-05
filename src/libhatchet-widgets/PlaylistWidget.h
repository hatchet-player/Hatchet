/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef HATCHET_WIDGETS_PLAYLISTWIDGET_H
#define HATCHET_WIDGETS_PLAYLISTWIDGET_H

#include "widgets/OverlayWidget.h"

#include <QListView>

#include "WidgetsDllMacro.h"

namespace Hatchet
{
  
namespace Widgets
{

class HATCHET_WIDGETS_EXPORT PlaylistWidget : public QListView
{
Q_OBJECT

public:
    PlaylistWidget( QWidget* parent = 0 );

    OverlayWidget* overlay() const { return m_overlay; }

    virtual void setModel( QAbstractItemModel* model );

signals:
    void modelChanged();

private slots:
    void verifySize();

private:
    OverlayWidget* m_overlay;
};

}; // Widgets

}; // Hatchet

#endif // HATCHET_WIDGETS_PLAYLISTWIDGET_H