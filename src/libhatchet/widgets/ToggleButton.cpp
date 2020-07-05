/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2011, Jeff Mitchell <jeff@tomahawk-player.org>
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

#include "ToggleButton.h"

#include "widgets/HeaderLabel.h"
#include "utils/HatchetStyle.h"
#include "utils/HatchetUtilsGui.h"

#include <QStylePainter>
#include <QStyleOptionButton>


ToggleButton::ToggleButton( QWidget* parent )
    : QLabel( parent )
    , m_checked( false )
{
    QFont f( font() );
    f.setBold( true );
    f.setPointSize( HatchetUtils::defaultFontSize() + 1 );

    setFont( f );
    setFixedHeight( QLabel::sizeHint().height() + 8 );

    setCursor( Qt::PointingHandCursor );
}


ToggleButton::~ToggleButton()
{
}


void
ToggleButton::setText( const QString& s )
{
    QLabel::setText( s );
    setFixedWidth( fontMetrics().width( text() ) + 32 );
}


void
ToggleButton::mouseReleaseEvent( QMouseEvent* event )
{
    QFrame::mouseReleaseEvent( event );

    m_checked ^= true;
    update();

    emit clicked();
}


void
ToggleButton::paintEvent( QPaintEvent* event )
{
    Q_UNUSED( event );

    QPainter p( this );

    p.save();
    QRect r = contentsRect();
    HatchetStyle::horizontalHeader( &p, r );
    p.restore();

    p.save();
    p.setRenderHint( QPainter::Antialiasing );
    p.setPen( Qt::white );

    {
        QRect highlightRect( r );
        highlightRect.adjust( 0, 2, 0, -3 );

        if ( isChecked() )
        {
            p.setBrush( HatchetStyle::TOGGLEBUTTON_HIGHLIGHT );
        }
        else
        {
            p.setBrush( HatchetStyle::TOGGLEBUTTON_BACKGROUND );
        }

        p.drawRoundedRect( highlightRect, 4.0, 4.0 );
    }

    QTextOption to( Qt::AlignCenter );
    r.adjust( 8, 0, -8, 0 );
    p.setBrush( HatchetStyle::TOGGLEBUTTON_TEXT );
    p.drawText( r, text(), to );

    p.restore();
}
