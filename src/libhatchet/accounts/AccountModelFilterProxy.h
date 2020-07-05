/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2012, Leo Franchi <lfranchi@kde.org>
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

#ifndef ACCOUNTMODELFILTERPROXY_H
#define ACCOUNTMODELFILTERPROXY_H

#include "Account.h"
#include "DllMacro.h"

#include <QSortFilterProxyModel>

namespace Hatchet {
namespace Accounts {

class DLLEXPORT AccountModelFilterProxy : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    AccountModelFilterProxy( QObject* parent = 0 );

    void setFilterType( Hatchet::Accounts::AccountType type );

    virtual void setSourceModel( QAbstractItemModel* sourceModel );

signals:
    void scrollTo( const QModelIndex& idx );

    void startInstalling( const QPersistentModelIndex& idx );
    void doneInstalling( const QPersistentModelIndex& idx );
    void errorInstalling( const QPersistentModelIndex& idx );

protected:
    virtual bool filterAcceptsRow ( int sourceRow, const QModelIndex& sourceParent ) const;

private slots:
    void onScrollTo( const QModelIndex& idx );

    void onStartInstalling( const QPersistentModelIndex& idx );
    void onDoneInstalling( const QPersistentModelIndex& idx );
    void onErrorInstalling( const QPersistentModelIndex& idx );

private:
    Hatchet::Accounts::AccountType m_filterType;
};

}

}
#endif // ACCOUNTMODELFILTERPROXY_H
