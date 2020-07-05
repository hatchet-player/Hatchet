/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2011,      Leo Franchi <lfranchi@kde.org>
 *   Copyright 2011,      Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2011-2016, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2013,      Uwe L. Korn <uwelk@xhochy.com>
 *   Copyright 2013,      Teo Mrnjavac <teo@kde.org>
 *   Copyright 2014,      Dominik Schmidt <domme@tomahawk-player.org>
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

#include "LinkGenerator.h"

#include "HatchetUtils.h"
#include "Logger.h"
#include "ShortLinkHelper.h"

#include "HatchetLinkGeneratorPlugin.h"

#include "../resolvers/SyncScriptJob.h"

#include <QClipboard>
#include <QApplication>
#include <QMetaObject>
#include <memory>


using namespace Hatchet;
using namespace Hatchet::Utils;

LinkGenerator* LinkGenerator::s_instance = 0;


LinkGenerator*
LinkGenerator::instance()
{
    if ( !s_instance )
        s_instance = new LinkGenerator;

    return s_instance;
}


LinkGenerator::LinkGenerator( QObject* parent )
    : QObject( parent )
{
    m_defaultPlugin.reset( new HatchetLinkGeneratorPlugin );
    m_plugins.append( m_defaultPlugin.get() );
}


LinkGenerator::~LinkGenerator()
{
}


void LinkGenerator::addPlugin( LinkGeneratorPlugin* plugin )
{
    m_plugins.append( plugin );
}


void
LinkGenerator::removePlugin( LinkGeneratorPlugin* plugin )
{
    m_plugins.removeAll( plugin );
}


void
LinkGenerator::copyScriptJobResultToClipboard( const QVariantMap& data )
{
    m_clipboardLongUrl = data[ "url" ].toUrl();

    if ( data[ "shortenLink" ].toBool() )
    {
        Hatchet::Utils::ShortLinkHelper* slh = new Hatchet::Utils::ShortLinkHelper();
        connect( slh, SIGNAL( shortLinkReady( QUrl, QUrl, QVariant ) ),
                SLOT( copyToClipboardReady( QUrl, QUrl, QVariant ) ) );
        connect( slh, SIGNAL( done() ),
                slh, SLOT( deleteLater() ),
                Qt::QueuedConnection );
        slh->shortenLink( m_clipboardLongUrl );
    }
    else
    {
        copyToClipboardReady( m_clipboardLongUrl, m_clipboardLongUrl );
    }

    sender()->deleteLater();
}


void
LinkGenerator::copyToClipboardReady( const QUrl& longUrl, const QUrl& shortUrl, const QVariant& )
{
    // Copy resulting url to clipboard
    if ( m_clipboardLongUrl == longUrl )
    {
        QClipboard* cb = QApplication::clipboard();

        QByteArray data = HatchetUtils::percentEncode( shortUrl.isEmpty() ? longUrl : shortUrl );
        cb->setText( data );

        m_clipboardLongUrl.clear();
    }
}
