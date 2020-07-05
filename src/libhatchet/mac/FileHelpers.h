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

#ifndef MAC_FILE_HELPERS_H
#define MAC_FILE_HELPERS_H

#import <Cocoa/Cocoa.h>

// Implement this delegate protocol to get notified about the result of your copy attempt
@interface NSObject (SUInstallerDelegateInformalProtocol)
- (void)moveFinished;
- (void)moveFailedWithError:(NSError *)error;
@end

@interface FileHelpers : NSObject
{}
// Move a file from point A to point B, asking for authentication if necessary
// Will be asynchronous: Implement the delegate protocol know about the completion
+ (void) moveFile:(NSString *)source to:(NSString*)dest withDelegate:delegate;

// Internal
+ (void)notifyDelegate:(NSDictionary *)info;

@end

#endif
