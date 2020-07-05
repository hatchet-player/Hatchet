/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012,      Teo Mrnjavac <teo@kde.org>
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

#ifndef ACCOUNTSTOOLBUTTON_H
#define ACCOUNTSTOOLBUTTON_H

#include "AccountsPopupWidget.h"

#include "accounts/AccountModel.h"
#include "AccountModelFactoryProxy.h"
#include "utils/DpiScaler.h"

#include <QToolButton>

class AccountsToolButton : public QToolButton, private HatchetUtils::DpiScaler
{
    Q_OBJECT
public:
    explicit AccountsToolButton( QWidget* parent = 0 );

    QSize sizeHint() const;

signals:
    void widthChanged();

protected:
    void mousePressEvent( QMouseEvent* event );
    void paintEvent( QPaintEvent* event );
    void moveEvent( QMoveEvent* event );

private slots:
    void popupHidden();
    void updateIcons();

private:
    AccountsPopupWidget* m_popup;
    Hatchet::Accounts::AccountModel *m_model;
    AccountModelFactoryProxy *m_proxy;

    QList< QPixmap > m_factoryPixmaps;
};

#endif // ACCOUNTSTOOLBUTTON_H
