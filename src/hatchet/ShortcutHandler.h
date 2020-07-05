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

#ifndef SHORTCUTHANDLER_H
#define SHORTCUTHANDLER_H

#include <QObject>

namespace Hatchet {
/**
  Base class for various shortcut plugins on different platforms
  */
class ShortcutHandler : public QObject
{
    Q_OBJECT
public:
    virtual ~ShortcutHandler();

signals:
    // add more as needed
    void playPause();
    void pause();
    void stop();
    void previous();
    void next();

    void volumeUp();
    void volumeDown();
    void mute();
protected:
    explicit ShortcutHandler( QObject *parent = 0 );

};

}

#endif // SHORTCUTHANDLER_H
