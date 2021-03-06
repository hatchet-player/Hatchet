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

#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include "DllMacro.h"

#include <QSslError>
#include <QWebEnginePage>

class QNetworkReply;

namespace Hatchet
{

class JSAccount;

class DLLEXPORT ScriptEngine : public QWebEnginePage
{
Q_OBJECT

public:
    explicit ScriptEngine( JSAccount* parent );

    QString userAgentForUrl( const QUrl& url ) const;
    void setScriptPath( const QString& scriptPath );

public slots:
    bool shouldInterruptJavaScript();
    void showWebInspector();

protected:
    virtual void javaScriptConsoleMessage( const QString& message, int lineNumber, const QString& sourceID );

private slots:
    void sslErrorHandler( QNetworkReply* qnr, const QList<QSslError>& errlist );

private:
    JSAccount* m_parent;
    QString m_scriptPath;
    QString m_header;
    // QScopedPointer< QWebInspector > m_webInspector; QT5.15 DISABLE
};

} // ns: Hatchet

#endif // SCRIPTENGINE_H
