/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Teo Mrnjavac <teo@kde.org>
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

#ifndef DPISCALER_H
#define DPISCALER_H

#include "DllMacro.h"

#include <QPaintDevice>
#include <QMargins>
#include <QSize>

namespace HatchetUtils
{

/**
 * @brief The DpiScaler class provides some convenience methods to recompute fixed pixel sizes
 * into values suitable for different environment DPI settings.
 * Usage:
 * class Foo : public QWidget, private HatchetUtils::DpiScaler {...};
 */
class DLLEXPORT DpiScaler
{
public:
    DpiScaler( const QPaintDevice* that );

    QSize scaled( int w, int h ) const;
    QSize scaled( const QSize& size ) const;
    QMargins scaled( int left, int top, int right, int bottom ) const;
    QMargins scaled( const QMargins& margins ) const;
    int scaledX( int x ) const;
    int scaledY( int y ) const;

    // convenience one-shot methods, usable without composing or private-inheriting DpiScaler
    static QSize scaled( const QPaintDevice* pd, int w, int h );
    static QSize scaled( const QPaintDevice* pd, const QSize& size );
    static QMargins scaled( const QPaintDevice* pd, int left, int top, int right, int bottom );
    static QMargins scaled( const QPaintDevice* pd, const QMargins& margins );
    static int scaledX( const QPaintDevice* pd, int x );
    static int scaledY( const QPaintDevice* pd, int y );
    static qreal ratioFromFontHeight();

private:
    inline static qreal ratioX( const QPaintDevice* pd );
    inline static qreal ratioY( const QPaintDevice* pd );

    qreal m_ratioX;
    qreal m_ratioY;

    const QPaintDevice* that;

    static const qreal s_baseDpi;
};

}

#endif // DPISCALER_H
