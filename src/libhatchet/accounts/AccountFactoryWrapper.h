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

#ifndef ACCOUNTFACTORYWRAPPER_H
#define ACCOUNTFACTORYWRAPPER_H

#include "DllMacro.h"

#include <QDialog>
#include <QModelIndex>

class QAbstractButton;
namespace Hatchet {
namespace Accounts {
    class AccountFactory;
class Account;
}
}

class Ui_AccountFactoryWrapper;

// class AccountFactoryWrapper_
class DLLEXPORT AccountFactoryWrapper : public QDialog
{
    Q_OBJECT
public:
    enum ExtraRoles {
        AccountRole = Qt::UserRole + 140
    };

    explicit AccountFactoryWrapper( Hatchet::Accounts::AccountFactory* factory, QWidget* parent = 0 );
    virtual ~AccountFactoryWrapper() {}

public slots:
    void openAccountConfig( Hatchet::Accounts::Account* );
    void removeAccount( Hatchet::Accounts::Account* );
    void accountCheckedOrUnchecked( const QModelIndex& , Hatchet::Accounts::Account* , Qt::CheckState );

private slots:
    void buttonClicked( QAbstractButton* );
    void load();

private:
    Hatchet::Accounts::AccountFactory* m_factory;
    Ui_AccountFactoryWrapper* m_ui;
    QPushButton* m_addButton;
};

#endif // ACCOUNTFACTORYWRAPPER_H
