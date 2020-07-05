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

#ifndef LOCALCONFIGSTORAGE_H
#define LOCALCONFIGSTORAGE_H

#include "ConfigStorage.h"

namespace Hatchet
{

namespace Accounts
{

class LocalConfigStorage : public ConfigStorage
{
    Q_OBJECT
public:
    explicit LocalConfigStorage( QObject* parent = nullptr );

    void init() override;

    QString id() const override;

    QStringList accountIds() const override;

    unsigned int priority() const override;

    void deduplicateFrom( const ConfigStorage* other ) override;

    void save( const QString& accountId, const Account::Configuration& cfg ) override;
    void load( const QString& accountId, Account::Configuration& cfg ) const override;
    void remove( const QString& accountId ) override;

#ifdef Q_OS_MAC
    static QString credentialsServiceName();
#endif

private slots:
    void onCredentialsManagerReady( const QString& service );

private:
    static const QString s_credentialsServiceName;
    QStringList m_accountIds;

    static LocalConfigStorage* s_instance;
};

} //namespace Accounts

} //namespace Hatchet

#endif // LOCALCONFIGSTORAGE_H
