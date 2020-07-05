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

#include "DatabaseCommand_RenamePlaylist.h"

#include "collection/Collection.h"
#include "network/Servent.h"
#include "utils/Logger.h"

#include "DatabaseImpl.h"
#include "PlaylistEntry.h"
#include "Source.h"

#include <QSqlQuery>

using namespace Hatchet;


DatabaseCommand_RenamePlaylist::DatabaseCommand_RenamePlaylist( const source_ptr& source, const QString& playlistguid, const QString& playlistTitle )
    : DatabaseCommandLoggable( source )
{
    setPlaylistguid( playlistguid );
    setPlaylistTitle( playlistTitle );
}


void
DatabaseCommand_RenamePlaylist::exec( DatabaseImpl* lib )
{
    HatchetSqlQuery cre = lib->newquery();

    QString sql = QString( "UPDATE playlist SET title = :title WHERE guid = :id AND source %1" )
                     .arg( source()->isLocal() ? "IS NULL" : QString( "= %1" ).arg( source()->id() ) );

    cre.prepare( sql );
    cre.bindValue( ":id", m_playlistguid );
    cre.bindValue( ":title", m_playlistTitle );

    qDebug() << Q_FUNC_INFO << m_playlistTitle << m_playlistguid;

    cre.exec();
}


void
DatabaseCommand_RenamePlaylist::postCommitHook()
{
    playlist_ptr playlist = Playlist::get( m_playlistguid );
    Q_ASSERT( !playlist.isNull() );
    if ( !playlist )
        return;

    tDebug() << "Renaming playlist" << playlist->title() << "to" << m_playlistTitle << m_playlistguid;
    playlist->setTitle( m_playlistTitle );

    if ( source()->isLocal() )
        Servent::instance()->triggerDBSync();
}
