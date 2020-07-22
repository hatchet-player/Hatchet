/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef CAPTIONLABEL_H
#define CAPTIONLABEL_H

#include "ClickableLabel.h"
#include "DllMacro.h"

/**
 * \class CaptionLabel
 * \brief A styled caption for use in pages, e.g. above playlists.
 */
class DLLEXPORT CaptionLabel : public ClickableLabel
{
    Q_OBJECT

public:
    CaptionLabel( QWidget* parent );
    ~CaptionLabel();

    QSize minimumSizeHint() const { return sizeHint(); }
    QSize sizeHint() const;

    static int defaultFontSize();

public slots:
    bool showCloseButton() const { return m_showCloseButton; }
    void setShowCloseButton( bool b );

protected:
    //    void changeEvent( QEvent* e );
    void paintEvent( QPaintEvent* event );

private:
    QWidget* m_parent;

    bool m_showCloseButton;
};

#endif // CAPTIONLABEL_H