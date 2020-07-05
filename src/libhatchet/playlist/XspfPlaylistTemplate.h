/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Uwe L. Korn <uwelk@xhochy.com>
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

#pragma once
#ifndef HATCHET_XSPFPLAYLISTTEMPLATE_H
#define HATCHET_XSPFPLAYLISTTEMPLATE_H

#include "playlist/PlaylistTemplate.h"

namespace Hatchet {

class XspfPlaylistTemplatePrivate;

/**
 * PlaylistTemplate for loading XSPF playlists.
 *
 * Be aware that get() should only be called after tracksLoaded was emitted.
 * Functions using this class that they handover this class
 * to other functions which work only on PlaylistTemplates should ensure
 * that tracksLoaded was emitted BEFORE passing on an object of this class.
 */
class XspfPlaylistTemplate : public Hatchet::PlaylistTemplate
{
    Q_OBJECT
public:
    XspfPlaylistTemplate( const QString& _url, const source_ptr& source, const QString& guid );
    virtual ~XspfPlaylistTemplate();

    virtual Hatchet::playlist_ptr get();

    /**
     * Fetch the XSPF and load all tracks.
     *
     * When loading is done, tracksLoaded will be emitted.
     */
    void load();

signals:
    void tracksLoaded( const QList< Hatchet::query_ptr >& tracks );

private slots:
    void xspfTracksLoaded( const QList< Hatchet::query_ptr >& tracks );

private:
    Q_DECLARE_PRIVATE( XspfPlaylistTemplate )
};

} // namespace Hatchet

#endif // HATCHET_XSPFPLAYLISTTEMPLATE_H
