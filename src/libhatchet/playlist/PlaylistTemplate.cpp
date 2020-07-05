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

#include "PlaylistTemplate_p.h"

#include "Source.h"

Hatchet::PlaylistTemplate::PlaylistTemplate(const Hatchet::source_ptr& author, const QString &guid, const QString &title, const QString &info, const QString &creator, bool shared, const QList<Hatchet::query_ptr> &queries)
    : QObject( 0 )
    , d_ptr( new PlaylistTemplatePrivate( this, author, guid, title, info, creator, shared, queries ) )
{
}


Hatchet::PlaylistTemplate::~PlaylistTemplate()
{
    tLog() << Q_FUNC_INFO;
    delete d_ptr;
}


Hatchet::playlist_ptr
Hatchet::PlaylistTemplate::get()
{
    Q_D( PlaylistTemplate );

    if ( d->playlist.isNull() )
    {
        // First try to load the playlist if already exists
        d->playlist = Playlist::get( d->guid );
    }

    if ( d->playlist.isNull() )
    {
        // This playlist does not exist yet, so create it.
        d->playlist = Playlist::create( d->author, d->guid, d->title, d->info, d->creator, d->shared, d->queries );
    }

    return d->playlist;
}


QList<Hatchet::query_ptr>
Hatchet::PlaylistTemplate::tracks() const
{
    Q_D( const PlaylistTemplate );

    return d->queries;
}

Hatchet::PlaylistTemplate::PlaylistTemplate( Hatchet::PlaylistTemplatePrivate* d )
    : QObject( 0 )
    , d_ptr( d )
{
}
