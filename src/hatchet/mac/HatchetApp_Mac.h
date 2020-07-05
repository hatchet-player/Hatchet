/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
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

#ifndef HATCHETAPP_MAC_H
#define HATCHETAPP_MAC_H

// this file and hatchet_app.mm copied and inspired by mac_startup.* in clementine player,
// copyright David Sansome 2010

class QString;
class QObject;
class HatchetWindow;

namespace Hatchet {

class MacShortcutHandler;

/// Interface between cocoa and hatchet
class PlatformInterface {
 public:
  // Called when the application should show itself.
  virtual void activate() = 0;
  virtual bool loadUrl( const QString& url ) = 0;

  virtual ~PlatformInterface() {}
};

void macMain();
void setShortcutHandler(Hatchet::MacShortcutHandler* engine);
// used for opening files with hatchet
void setApplicationHandler(PlatformInterface* handler);
void checkForUpdates();

// Pass in a QObject with slots "fullScreenEntered() and fullScreenExited() in order to be notified
void toggleFullscreen();
void enableFullscreen( QObject* notifier );

void setupToolBarMac( HatchetWindow* parent );

};

#endif
