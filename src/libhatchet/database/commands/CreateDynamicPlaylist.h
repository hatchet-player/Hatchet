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

#ifndef DATABASECOMMAND_CREATEDYNAMICPLAYLIST_H
#define DATABASECOMMAND_CREATEDYNAMICPLAYLIST_H

#include "Typedefs.h"
#include "CreatePlaylist.h"

namespace Hatchet
{

/**
 * Create a new dynamic playlist in the database, based on an existing playlist.
 *
 * If autoLoad is true, this playlist will *not* show up in the sidebar under the playlist tree, and
 *  it will *not* be replicated to peers. It is useful to show a "specially crafted" playlist in other places
 */

class DatabaseCommand_CreateDynamicPlaylist : public DatabaseCommand_CreatePlaylist
{
    Q_OBJECT
    Q_PROPERTY( QVariant playlist READ playlistV WRITE setPlaylistV )

public:
    explicit DatabaseCommand_CreateDynamicPlaylist( QObject* parent = 0 );
    explicit DatabaseCommand_CreateDynamicPlaylist( const Hatchet::source_ptr& author, const Hatchet::dynplaylist_ptr& playlist, bool autoLoad = true );
    virtual ~DatabaseCommand_CreateDynamicPlaylist();

    QString commandname() const { return "createdynamicplaylist"; }

    virtual void exec( DatabaseImpl* lib );
    virtual void postCommitHook();
    virtual bool doesMutates() const { return true; }

    virtual bool loggable() const { return m_autoLoad; }

    QVariant playlistV() const;

    void setPlaylistV( const QVariant& v )
    {
        m_v = v;
    }

protected:
    virtual bool report() { return m_autoLoad; }

private:
    Hatchet::dynplaylist_ptr m_playlist;
    bool m_autoLoad;
};

}

#endif // DATABASECOMMAND_CREATEDYNAMICPLAYLIST_H
