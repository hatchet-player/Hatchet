/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include "HeaderLabel.h"

#include <QPainter>

#include "utils/Logger.h"
#include "utils/HatchetStyle.h"
#include "utils/HatchetUtilsGui.h"


HeaderLabel::HeaderLabel( QWidget* parent )
    : ClickableLabel( parent )
    , m_parent( parent )
{
    QFont f( font() );
    f.setBold( true );
    f.setPointSize( HatchetUtils::defaultFontSize() );
    setFont( f );

    setFixedHeight( HatchetUtils::defaultFontHeight() * 1.4 );
    setMouseTracking( true );
}


HeaderLabel::~HeaderLabel()
{
}


QSize
HeaderLabel::sizeHint() const
{
    return QLabel::sizeHint();
}


void
HeaderLabel::paintEvent( QPaintEvent* /* event */ )
{
    QPainter p( this );
    QRect r = contentsRect();
    HatchetStyle::horizontalHeader( &p, r );

    QTextOption to( alignment() | Qt::AlignVCenter );
    r.adjust( 8, 0, -8, 0 );
    p.setPen( HatchetStyle::HEADER_TEXT );
    p.drawText( r, text(), to );
}
