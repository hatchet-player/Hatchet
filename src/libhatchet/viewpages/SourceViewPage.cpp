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

#include "SourceViewPage.h"
#include "ui_SourceViewPage.h"

#include "Source.h"
#include "ViewManager.h"

#include "playlist/AlbumModel.h"
#include "playlist/RecentlyAddedModel.h"
#include "playlist/RecentlyPlayedModel.h"

#include "database/Database.h"
#include "database/DatabaseCommand_AllAlbums.h"

#include "utils/HatchetUtilsGui.h"
#include "utils/Logger.h"


SourceInfoWidget::SourceInfoWidget( const Hatchet::source_ptr& source, QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::SourceInfoWidget )
    , m_source( source )
{
    ui->setupUi( this );

    HatchetUtils::unmarginLayout( layout() );
    HatchetUtils::unmarginLayout( ui->horizontalLayout );
    HatchetUtils::unmarginLayout( ui->verticalLayout );
    HatchetUtils::unmarginLayout( ui->verticalLayout_2 );
    HatchetUtils::unmarginLayout( ui->verticalLayout_3 );

    ui->splitter->setStretchFactor( 0, 0 );
    ui->splitter->setStretchFactor( 1, 1 );

    m_recentTracksModel = new RecentlyAddedModel( ui->recentCollectionView );
    ui->recentCollectionView->proxyModel()->setStyle( PlayableProxyModel::SingleColumn );
    ui->recentCollectionView->setPlayableModel( m_recentTracksModel );
    ui->recentCollectionView->sortByColumn( PlayableModel::Age, Qt::DescendingOrder );
    m_recentTracksModel->setSource( source );

    m_historyModel = new RecentlyPlayedModel( ui->historyView );
    ui->historyView->proxyModel()->setStyle( PlayableProxyModel::SingleColumn );
    ui->historyView->setPlayableModel( m_historyModel );
    m_historyModel->setSource( source );

    m_recentAlbumModel = new AlbumModel( ui->recentAlbumView );
    ui->recentAlbumView->setPlayableModel( m_recentAlbumModel );
    ui->recentAlbumView->proxyModel()->sort( -1 );

    onCollectionChanged();
    connect( source->dbCollection().data(), SIGNAL( changed() ), SLOT( onCollectionChanged() ) );

    m_title = tr( "New Additions" );
    if ( source->isLocal() )
    {
        m_description = tr( "My recent activity" );
    }
    else
    {
        m_description = tr( "Recent activity from %1" ).arg( source->friendlyName() );
    }
}


SourceInfoWidget::~SourceInfoWidget()
{
    delete ui;
}


void
SourceInfoWidget::onCollectionChanged()
{
    loadRecentAdditions();
}


void
SourceInfoWidget::loadRecentAdditions()
{
    m_recentAlbumModel->addFilteredCollection( m_source->dbCollection(), 20, Hatchet::DatabaseCommand_AllAlbums::ModificationTime, true );
}


void
SourceInfoWidget::changeEvent( QEvent* e )
{
    QWidget::changeEvent( e );
    switch ( e->type() )
    {
        case QEvent::LanguageChange:
            ui->retranslateUi( this );
            break;

        default:
            break;
    }
}


QPixmap
SourceInfoWidget::pixmap() const
{
    return HatchetUtils::defaultPixmap( HatchetUtils::NewAdditions, HatchetUtils::Original );

}
