/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013, Teo Mrnjavac <teo@kde.org>
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

#include "ScriptCollectionHeader.h"

#include "utils/ImageRegistry.h"
#include "widgets/ElidedLabel.h"

#include <QBoxLayout>
#include <QPushButton>

ScriptCollectionHeader::ScriptCollectionHeader( QWidget* parent )
    : FilterHeader( parent )
{
    m_refreshButton = new QPushButton( this );
    m_refreshButton->setFlat( true );
    m_refreshButton->setStyleSheet( "QPushButton { border: 0px; background: transparent; }" );
    QHBoxLayout* descLayout = new QHBoxLayout;
    ui->horizontalLayout->addLayout( descLayout );
//    descLayout->addWidget( m_descriptionLabel );
    HatchetUtils::unmarginLayout( descLayout );
//    descLayout->addSpacing( m_descriptionLabel->fontMetrics().height() / 2 );
    descLayout->addWidget( m_refreshButton );
    descLayout->addStretch();

    m_refreshButton->setIcon( ImageRegistry::instance()->pixmap( RESPATH "images/refresh.svg", QSize( ui->captionLabel->fontMetrics().height(),
                                                                                                      ui->captionLabel->fontMetrics().height() ), HatchetUtils::DropShadow ) );
    m_refreshButton->setFixedSize( ui->captionLabel->fontMetrics().height() + ui->captionLabel->margin() * 2,
                                   ui->captionLabel->fontMetrics().height() + ui->captionLabel->margin() * 2 );

    connect( m_refreshButton, SIGNAL( clicked() ), SIGNAL( refreshClicked() ) );
    m_refreshButton->hide();
    m_refreshButton->setToolTip( tr( "Reload Collection" ) );
}


void
ScriptCollectionHeader::setRefreshVisible( bool visible )
{
    m_refreshButton->setVisible( visible );
}
