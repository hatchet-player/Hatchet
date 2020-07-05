/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012, Teo Mrnjavac <teo@kde.org>
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

#ifndef ACCOUNTMODELFACTORYPROXY_H
#define ACCOUNTMODELFACTORYPROXY_H

#include "accounts/Account.h"
#include "accounts/AccountModel.h"

#include <QSortFilterProxyModel>


class AccountModelFactoryProxy : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit AccountModelFactoryProxy( QObject* parent = 0 );
    
    void setFilterEnabled( bool enabled );

    void setFilterRowType( Hatchet::Accounts::AccountModel::RowType rowType );

protected:
    virtual bool filterAcceptsRow ( int sourceRow, const QModelIndex& sourceParent ) const;

private:
    bool m_filterEnabled;
    Hatchet::Accounts::AccountModel::RowType m_filterRowType;
};

#endif // ACCOUNTMODELFACTORYPROXY_H
