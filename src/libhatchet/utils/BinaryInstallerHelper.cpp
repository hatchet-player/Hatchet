/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012 Leo Franchi <lfranchi@kde.org>
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

#include "BinaryInstallerHelper.h"

#include "accounts/AccountManager.h"
#include "HatchetSettings.h"
#include <QTemporaryFile>

BinaryInstallerHelper::BinaryInstallerHelper( QTemporaryFile* tempFile, const QString& resolverId, bool createAccount, AtticaManager* manager )
    : QObject( manager )
    , m_tempFile( tempFile )
    , m_resolverId( resolverId )
    , m_createAccount( createAccount )
    , m_manager( QPointer< AtticaManager >( manager ) )
{
    Q_ASSERT( m_tempFile );
    Q_ASSERT( !m_resolverId.isEmpty() );
    Q_ASSERT( !m_manager.isNull() );

    setProperty( "resolverid", m_resolverId );
}


BinaryInstallerHelper::~BinaryInstallerHelper()
{
    Q_ASSERT( m_tempFile );
    delete m_tempFile;
}


void
BinaryInstallerHelper::installSucceeded( const QString& path )
{
    qDebug() << Q_FUNC_INFO << "install of binary resolver succeeded, enabling: " << path;

    if ( m_manager.isNull() )
        return;

    if ( m_createAccount )
    {
        Hatchet::Accounts::Account* acct = Hatchet::Accounts::AccountManager::instance()->accountFromPath( path );

        Hatchet::Accounts::AccountManager::instance()->addAccount( acct );
        HatchetSettings::instance()->addAccount( acct->accountId() );
        Hatchet::Accounts::AccountManager::instance()->enableAccount( acct );
    }

    m_manager.data()->m_resolverStates[ m_resolverId ].scriptPath = path;
    m_manager.data()->m_resolverStates[ m_resolverId ].state = AtticaManager::Installed;

    HatchetSettings::instance()->setAtticaResolverStates( m_manager.data()->m_resolverStates );
    emit m_manager.data()->resolverInstalled( m_resolverId );
    emit m_manager.data()->resolverStateChanged( m_resolverId );

    deleteLater();
}
void BinaryInstallerHelper::installFailed()
{
    qDebug() << Q_FUNC_INFO << "install failed";

    if ( m_manager.isNull() )
        return;

    m_manager.data()->resolverInstallationFailed( m_resolverId );

    deleteLater();
}
