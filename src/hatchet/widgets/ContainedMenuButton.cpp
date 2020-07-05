/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012,      Teo Mrnjavac   <teo@kde.org>
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

#include "ContainedMenuButton.h"

#include <QMouseEvent>

#include "utils/HatchetUtilsGui.h"

ContainedMenuButton::ContainedMenuButton( QWidget *parent )
    : QToolButton( parent )
{
}

void
ContainedMenuButton::setMenu( QMenu *menu )
{
    m_menu = menu;
    m_menu->setFont( HatchetUtils::systemFont() );
    connect( m_menu, SIGNAL( aboutToHide() ), SLOT( menuHidden() ) );
}

void
ContainedMenuButton::mousePressEvent( QMouseEvent* event )
{
    if( m_menu )
    {
        QPoint myPos = mapToGlobal( rect().bottomRight() );
        myPos.rx() -= m_menu->sizeHint().width();
        m_menu->popup( myPos );
        event->accept();
    }
    QToolButton::mousePressEvent( event );
}

void
ContainedMenuButton::menuHidden()
{
    setDown( false );
}


QMenu*
ContainedMenuButton::menu() const
{
    return m_menu;
}
