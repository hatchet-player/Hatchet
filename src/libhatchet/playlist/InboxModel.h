/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Teo Mrnjavac <teo@kde.org>
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

#ifndef INBOXMODEL_H
#define INBOXMODEL_H

#include "PlaylistModel.h"
#include "Typedefs.h"
#include "DllMacro.h"
#include "jobview/InboxJobItem.h"


class DLLEXPORT InboxModel : public PlaylistModel
{
    Q_OBJECT
public:
    explicit InboxModel( QObject* parent = 0 );
    virtual ~InboxModel();

    virtual int unlistenedCount( const QModelIndex& parent = QModelIndex() ) const;

public slots:
    /**
     * Reimplemented from PlaylistModel, all track insertions/appends go through this method.
     * On top of PlaylistModel functionality, adds deduplication/grouping of equivalent tracks
     * sent from different sources.
     */
    virtual void insertEntries( const QList< Hatchet::plentry_ptr >& entries, int row = 0, const QModelIndex& parent = QModelIndex(), const QList< Hatchet::PlaybackLog >& logs = QList< Hatchet::PlaybackLog >() );

    virtual void removeIndex( const QModelIndex &index, bool moreToCome );

    virtual void clear();

    virtual void showNotification( InboxJobItem::Side side,
                                   const Hatchet::source_ptr& src,
                                   const Hatchet::trackdata_ptr& track ); //for lack of a better place to put this
    virtual void showNotification( InboxJobItem::Side side,
                                   const QString& dbid,
                                   const Hatchet::trackdata_ptr& track );

    virtual void markAsListened( const QModelIndexList& indexes );


private slots:
    void loadTracks();

    void tracksLoaded( QList< Hatchet::query_ptr > );

    void onDbcmdCreated( const Hatchet::dbcmd_ptr& cmd );
    void onDbcmdCommitted( const Hatchet::dbcmd_ptr& cmd );

private:
    static QList< Hatchet::SocialAction > mergeSocialActions( QList< Hatchet::SocialAction > first,
                                                               QList< Hatchet::SocialAction > second );
};

#endif // INBOXMODEL_H
