/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2013, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#include "ResultUrlChecker.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>

#include "Query.h"
#include "Result.h"
#include "Source.h"
#include "utils/Logger.h"
#include "utils/NetworkAccessManager.h"

using namespace Hatchet;


ResultUrlChecker::ResultUrlChecker( const query_ptr& query, QObject* userData,
        const QList< result_ptr >& results )
    : QObject( 0 )
    , m_query( query )
    , m_userData( userData )
    , m_results( results )
{
    check();
}


ResultUrlChecker::~ResultUrlChecker()
{
}


void
ResultUrlChecker::check()
{
    foreach ( const result_ptr& result, m_results )
    {
        tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "Checking http url:" << result->url();
        QUrl url = QUrl::fromUserInput( result->url() );
        if ( url.isEmpty() || !url.toString().startsWith( "http" ) )
            continue;

        NetworkReply* reply = new NetworkReply( Hatchet::Utils::nam()->head( QNetworkRequest( url ) ) );
        m_replies.insert( reply, result );
        connect( reply, SIGNAL( finished() ), SLOT( headFinished() ) );
    }
}


void
ResultUrlChecker::headFinished()
{
    NetworkReply* r = qobject_cast<NetworkReply*>( sender() );
    r->deleteLater();

    if ( !m_replies.contains( r ) )
        return;

    result_ptr result = m_replies.value( r );
    m_replies.remove( r );

    if ( r->reply()->error() == QNetworkReply::NoError )
    {
        tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "Found valid http url:" << result->url();
        m_validResults << result;
    }
    else
        tDebug( LOGVERBOSE ) << Q_FUNC_INFO << "Found invalid http url:" << result->url() << r->reply()->error();

    if ( m_replies.isEmpty() )
        emit done();
}
