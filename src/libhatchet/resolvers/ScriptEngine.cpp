/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2013,      Teo Mrnjavac <teo@kde.org>
 *   Copyright 2013,      Uwe L. Korn <uwelk@xhochy.com>
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

#include "ScriptEngine.h"

#include "jobview/ScriptErrorStatusMessage.h"
#include "jobview/JobStatusModel.h"
#include "jobview/JobStatusView.h"
#include "utils/Logger.h"
#include "utils/HatchetUtils.h"
#include "utils/HatchetUtilsGui.h"
#include "HatchetSettings.h"
#include "HatchetVersion.h"
#include "JSAccount.h"

#include <QDir>
#include <QMessageBox>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QCoreApplication>

using namespace Hatchet;

ScriptEngine::ScriptEngine( JSAccount* parent )
    : QWebEnginePage( (QObject*) parent )
    , m_parent( parent )
{   
    // QT5.15 DISABLE
    // settings()->setAttribute( QWebEngineSettings::OfflineStorageDatabaseEnabled, true );
    // settings()->setOfflineStoragePath( HatchetUtils::appDataDir().path() );
    // settings()->setAttribute(QWebEngineSettings::WebAttribute LocalStorageEnabled, true);
    // settings()->setLocalStoragePath( HatchetUtils::appDataDir().path() );
    // settings()->setAttribute( QWebEngineSettings::LocalStorageDatabaseEnabled, true );
    // settings()->setAttribute( QWebEngineSettings::LocalContentCanAccessFileUrls, true );
    // settings()->setAttribute( QWebEngineSettings::LocalContentCanAccessRemoteUrls, true );
    // settings()->setOfflineStorageDefaultQuota(100 * 1024 * 1024 /* 100 Mb */);
    // settings()->setOfflineWebApplicationCacheQuota(100 * 1024 * 1024 /* 100 Mb */);
    // settings()->setAttribute( QWebEngineSettings::DeveloperExtrasEnabled, true );

    // HACK
    QStringList cmdArgs = QCoreApplication::instance()->arguments();
    int position = cmdArgs.indexOf( "--show-inspector" ) + 1;
    if ( position > 0 &&  !cmdArgs.at( position ).isEmpty() && parent->name().contains( cmdArgs.at( position ), Qt::CaseInsensitive ) ) {
        QMetaObject::invokeMethod( this, "showWebInspector", Qt::QueuedConnection );
    }

    // Hatchet is not a user agent
    QWebEngineProfile profile;
    QWebEnginePage m_header(&profile);
    
    profile.setHttpUserAgent(QString( "%1/%2" )
               .arg( HATCHET_APPLICATION_NAME )
               .arg( HATCHET_VERSION ) );
    
    // The user agent is updated after a page load.
    m_header.load(QUrl("about:blank"));

    tLog( LOGVERBOSE ) << "JSResolver Using header" << profile.httpUserAgent();

    m_header.setHtml( "<html><body></body></html>", QUrl( "file:///invalid/file/for/security/policy" ) );

    connect(&m_header, SIGNAL( sslErrors( QNetworkReply*, QList<QSslError> ) ),
                       SLOT( sslErrorHandler( QNetworkReply*, QList<QSslError> ) ) );
}


void
ScriptEngine::javaScriptConsoleMessage( const QString& message, int lineNumber, const QString& sourceID )
{
    tLog() << "JAVASCRIPT:" << QString( "%1:%2" ).arg( m_scriptPath ).arg( lineNumber ) << message << sourceID;
    #ifdef QT_DEBUG
    QFileInfo scriptPath( m_scriptPath );
    JobStatusView::instance()->model()->addJob( new ScriptErrorStatusMessage( tr( "%1:%2 %3" ).arg( scriptPath.fileName() ).arg( lineNumber ).arg( message ), m_parent ) );
    #endif
}


void
ScriptEngine::sslErrorHandler( QNetworkReply* qnr, const QList<QSslError>& errlist )
{
    tDebug() << Q_FUNC_INFO;

    QByteArray digest = errlist.first().certificate().digest();

    if ( !HatchetSettings::instance()->isSslCertKnown( digest ) )
    {
        foreach ( const QSslError& err, errlist )
            tDebug() << Q_FUNC_INFO << "SSL error:" << err;

        QMessageBox question( HatchetUtils::hatchetWindow() );
        question.setWindowTitle( tr( "SSL Error" ) );
        question.setText( tr( "You have asked %applicationName to connect securely to <b>%1</b>, but we can't confirm that your connection is secure:<br><br>"
                            "<b>%2</b><br><br>"
                            "Do you want to trust this connection?" )
                            .arg( qnr->url().host() )
                            .arg( errlist.first().errorString() ) );

        question.setStandardButtons( QMessageBox::No );
        question.addButton( tr( "Trust certificate" ), QMessageBox::AcceptRole );

        int result = question.exec();

        //FIXME: discuss whether we want to store rejects, too (needs settings management to remove the decision?)
        if ( result == QMessageBox::AcceptRole )
            HatchetSettings::instance()->setSslCertTrusted( digest, result == QMessageBox::AcceptRole );
    }

    if ( HatchetSettings::instance()->isSslCertTrusted( digest ) )
    {
        qnr->ignoreSslErrors();
    }
}


QString
ScriptEngine::userAgentForUrl( const QUrl& url ) const
{
    Q_UNUSED( url );
    return m_header;
}


void
ScriptEngine::setScriptPath( const QString& scriptPath )
{
    m_scriptPath = scriptPath;
}


void
ScriptEngine::showWebInspector()
{
    /* QT5.15 DISABLE
    if ( m_webInspector.isNull() )
    {
        m_webInspector.reset( new QWebInspector() );
        m_webInspector->setPage( this );
        m_webInspector->setMinimumWidth( 800 );
        m_webInspector->setMinimumHeight( 600 );
    }

    m_webInspector->show();
    */
}


bool
ScriptEngine::shouldInterruptJavaScript()
{
    return true;
}

