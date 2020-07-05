/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef VIEWPAGE_H
#define VIEWPAGE_H

#include "Typedefs.h"
#include "PlaylistInterface.h"
#include "Artist.h"
#include "Album.h"
#include "Source.h"
#include "utils/HatchetUtils.h"
#include "playlist/PlaylistUpdaterInterface.h"

#include <QtGui/QPixmap>

namespace Hatchet
{


class DLLEXPORT ViewPage
{
public:
    enum DescriptionType {
        TextType = 0,
        ArtistType = 1,
        AlbumType = 2
    };

    ViewPage() {}
    virtual ~ViewPage();

    virtual QWidget* widget() = 0;
    virtual Hatchet::playlistinterface_ptr playlistInterface() const = 0;

    virtual QString title() const = 0;

    virtual DescriptionType descriptionType() { return TextType; }
    virtual QString description() const = 0;
    virtual Hatchet::artist_ptr descriptionArtist() const { return Hatchet::artist_ptr(); }
    virtual Hatchet::album_ptr descriptionAlbum() const { return Hatchet::album_ptr(); }

    virtual QString longDescription() const { return QString(); }
    virtual QPixmap pixmap() const { return QPixmap( RESPATH "icons/hatchet-icon-128x128.png" ); }

    virtual bool queueVisible() const { return true; }

    virtual QString filter() const { return m_filter; }
    virtual bool setFilter( const QString& filter );

    virtual bool willAcceptDrag( const QMimeData* data ) const;
    virtual bool dropMimeData( const QMimeData*, Qt::DropAction );

    virtual bool jumpToCurrentTrack() = 0;

    virtual bool isTemporaryPage() const { return false; }

    /**
     * Should we add a row in the SourceTreeView for this page.
     */
    virtual bool addPageItem() const;

    virtual bool isRemovable() const { return false; }

    /**
     * This page is actually a constant page that will be shown on every
     * restart of Hatchet until the user selects it to be removed.
     *
     * The main distinction between this and isTemporaryPage() is that the
     * page will not be listed in the search history.
     */
    virtual bool isDeletable() const { return false; }

    /**
     * The ViewPage item in the SourcesModel was deleted.
     */
    virtual void onItemDeleted();

    virtual bool isBeingPlayed() const { return false; }

    virtual QList<PlaylistUpdaterInterface*> updaters() const { return QList<PlaylistUpdaterInterface*>(); }

    /** subclasses implementing ViewPage can emit the following signals:
     * nameChanged( const QString& )
     * descriptionChanged( const QString& )
     * descriptionChanged( const Hatchet::artist_ptr& artist )
     * descriptionChanged( const Hatchet::album_ptr& album )
     * longDescriptionChanged( const QString& )
     * pixmapChanged( const QPixmap& )
     * destroyed( QWidget* widget );
     *
     * See DynamicWidget for an example
     */

private:
    QString m_filter;
};

} // ns

Q_DECLARE_METATYPE( Hatchet::ViewPage* )

#endif //VIEWPAGE_H
