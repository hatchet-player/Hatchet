/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012, Leo Franchi <lfranchi@kde.org
 *
 *   Hatchet is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hatchet is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hatchet. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HATCHETUTILS_MAC_H
#define HATCHETUTILS_MAC_H

#include <QObject>

#import <Foundation/Foundation.h>

@interface MoveDelegate : NSObject
{
    QObject* receiver;
    QString path;
}
- (void)setReceiver:(QObject*)receiver;
- (void)setMoveTo:(QString)path;
- (void)moveFinished;
- (void)moveFailedWithError:(NSError *)error;
@end

#endif // HATCHETUTILS_MAC_H
