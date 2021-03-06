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

#include "PlaylistDelegate.h"

#include "playlist/dynamic/GeneratorInterface.h"
#include "utils/HatchetStyle.h"
#include "utils/HatchetUtils.h"
#include "utils/HatchetUtilsGui.h"
#include "utils/Logger.h"

#include <QApplication>
#include <QPainter>

#include "widgets/RecentlyPlayedPlaylistsModel.h"

namespace Hatchet
{

namespace Widgets
{

QSize
PlaylistDelegate::sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    Q_UNUSED( option );
    Q_UNUSED( index );

    // Calculates the size for the bold line + 3 normal lines + margins
    int height = 2 * 6; // margins
    QFont font = option.font;
    QFontMetrics fm1( font );
    font.setPointSize( HatchetUtils::defaultFontSize() - 1 );
    height += fm1.height() * 3;
    font.setPointSize( HatchetUtils::defaultFontSize() );
    QFontMetrics fm2( font );
    height += fm2.height();

    return QSize( 0, height );
}


PlaylistDelegate::PlaylistDelegate()
{
}


void
PlaylistDelegate::paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption( &opt, QModelIndex() );
    qApp->style()->drawControl( QStyle::CE_ItemViewItem, &opt, painter );

    if ( option.state & QStyle::State_Selected && option.state & QStyle::State_Active )
    {
        opt.palette.setColor( QPalette::Text, opt.palette.color( QPalette::HighlightedText ) );
    }

    painter->save();
    painter->setRenderHint( QPainter::Antialiasing );
    painter->setPen( opt.palette.color( QPalette::Text ) );

    QTextOption to;
    to.setAlignment( Qt::AlignCenter );
    QFont font = opt.font;
    font.setPointSize( HatchetUtils::defaultFontSize() - 1 );

    QFont boldFont = font;
    boldFont.setBold( true );
    boldFont.setPointSize( HatchetUtils::defaultFontSize() );
    QFontMetrics boldFontMetrics( boldFont );

    QFont figFont = boldFont;
    figFont.setPointSize( HatchetUtils::defaultFontSize() - 1 );

    QRect pixmapRect = option.rect.adjusted( 12, 12, -option.rect.width() + option.rect.height() - 12, -12 );
    QPixmap avatar = index.data( RecentlyPlayedPlaylistsModel::PlaylistRole ).value< Hatchet::playlist_ptr >()->author()->avatar( HatchetUtils::RoundedCorners, pixmapRect.size(), true );
    painter->drawPixmap( pixmapRect, avatar );

    pixmapRect = QRect( option.rect.width() - option.fontMetrics.height() * 2.5 - 10, option.rect.top() + option.rect.height() / 4, option.fontMetrics.height() * 2.5, option.fontMetrics.height() * 2.5 );
    QPixmap icon;
    RecentlyPlayedPlaylistsModel::PlaylistTypes type = (RecentlyPlayedPlaylistsModel::PlaylistTypes)index.data( RecentlyPlayedPlaylistsModel::PlaylistTypeRole ).toInt();

    if ( type == RecentlyPlayedPlaylistsModel::StaticPlaylist )
        icon = HatchetUtils::defaultPixmap( HatchetUtils::Playlist, HatchetUtils::Original, pixmapRect.size() );
    else if ( type == RecentlyPlayedPlaylistsModel::AutoPlaylist )
        icon = HatchetUtils::defaultPixmap( HatchetUtils::AutomaticPlaylist, HatchetUtils::Original, pixmapRect.size() );
    else if ( type == RecentlyPlayedPlaylistsModel::Station )
        icon = HatchetUtils::defaultPixmap( HatchetUtils::Station, HatchetUtils::Original, pixmapRect.size() );

    painter->drawPixmap( pixmapRect, icon );

    if ( type != RecentlyPlayedPlaylistsModel::Station )
    {
        painter->save();
        painter->setFont( figFont );
        QString tracks = index.data( RecentlyPlayedPlaylistsModel::TrackCountRole ).toString();
        int width = painter->fontMetrics().width( tracks );
//         int bottomEdge = pixmapRect
        // right edge 10px past right edge of pixmapRect
        // bottom edge flush with bottom of pixmap
        QRect rect( pixmapRect.right() - width, 0, width - 8, 0 );
        rect.adjust( -2, 0, 0, 0 );
        rect.setTop( pixmapRect.bottom() - painter->fontMetrics().height() - 1 );
        rect.setBottom( pixmapRect.bottom() + 1 );

        QColor figColor( HatchetStyle::DASHBOARD_ROUNDFIGURE_BACKGROUND );
        painter->setPen( Qt::white );
        painter->setBrush( figColor );

        HatchetUtils::drawBackgroundAndNumbers( painter, tracks, rect );
        painter->restore();
    }

    painter->setFont( font );
    QString author = index.data( RecentlyPlayedPlaylistsModel::PlaylistRole ).value< Hatchet::playlist_ptr >()->author()->friendlyName();
    if ( author.indexOf( '@' ) > 0 )
        author = author.mid( 0, author.indexOf( '@' ) );

/*    const int w = painter->fontMetrics().width( author ) + 2;
    QRect avatarNameRect( opt.rect.width() - 10 - w, r.bottom(), w, opt.rect.bottom() - r.bottom() );
    painter->drawText( avatarNameRect, author, QTextOption( Qt::AlignCenter ) );

    const int leftEdge = opt.rect.width() - qMin( avatarNameRect.left(), r.left() );*/
    const int leftEdge = opt.rect.width() - pixmapRect.left();
    QString descText;
    if ( type == RecentlyPlayedPlaylistsModel::Station )
    {
        descText = index.data( RecentlyPlayedPlaylistsModel::DynamicPlaylistRole ).value< Hatchet::dynplaylist_ptr >()->generator()->sentenceSummary();
    }
    else
    {
        descText = index.data( RecentlyPlayedPlaylistsModel::ArtistRole ).toString();
    }

    QColor c = painter->pen().color();
    if ( !( option.state & QStyle::State_Selected && option.state & QStyle::State_Active ) )
    {
        painter->setPen( opt.palette.text().color().darker() );
    }

    QRect rectText = option.rect.adjusted( option.fontMetrics.height() * 5.5, boldFontMetrics.height() + 6, -leftEdge - 10, -8 );
#ifdef Q_OS_MAC
    rectText.adjust( 0, 1, 0, 0 );
#elif defined Q_OS_WIN
    rectText.adjust( 0, 2, 0, 0 );
#endif

    painter->drawText( rectText, descText );
    painter->setPen( c );
    painter->setFont( font );

    painter->setFont( boldFont );
    painter->drawText( option.rect.adjusted( option.fontMetrics.height() * 5, 6, -100, -option.rect.height() + boldFontMetrics.height() + 6 ), index.data().toString() );

    painter->restore();
}

}

}
