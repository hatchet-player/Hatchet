#include "XspfPlaylistTemplate_p.h"

namespace Hatchet {

XspfPlaylistTemplate::XspfPlaylistTemplate( const QString& _url, const source_ptr& source, const QString& guid )
    : PlaylistTemplate( new XspfPlaylistTemplatePrivate( this, _url, source, guid ) )
{
    Q_D( XspfPlaylistTemplate );

    connect( d->xspfLoader.data(), SIGNAL( tracks( QList<Hatchet::query_ptr> ) ),
             SLOT( xspfTracksLoaded( QList<Hatchet::query_ptr> ) ) );
}


XspfPlaylistTemplate::~XspfPlaylistTemplate()
{
}


playlist_ptr XspfPlaylistTemplate::get()
{
    Q_D( XspfPlaylistTemplate );

    return d->xspfLoader->getPlaylistForRecentUrl();
}


void
XspfPlaylistTemplate::load()
{
    Q_D( XspfPlaylistTemplate );

    d->xspfLoader->load( d->url );
}


void
XspfPlaylistTemplate::xspfTracksLoaded( const QList< Hatchet::query_ptr >& tracks )
{
    Q_D( XspfPlaylistTemplate );

    d->queries = tracks;
    emit tracksLoaded( tracks );
}


} // namespace Hatchet
