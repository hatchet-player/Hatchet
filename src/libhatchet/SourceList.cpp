/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2013,      Teo Mrnjavac <teo@kde.org>
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

#include "SourceList.h"

#include "database/Database.h"
#include "database/DatabaseImpl.h"
#include "database/commands/LoadAllSources.h"
#include "network/RemoteCollection.h"
#include "network/ControlConnection.h"
#include "infosystem/InfoSystemCache.h"
#include "resolvers/ExternalResolver.h"
#include "resolvers/ScriptCollection.h"
#include "utils/Json.h"
#include "utils/Logger.h"

using namespace Hatchet;

SourceList* SourceList::s_instance = 0;


SourceList*
SourceList::instance()
{
    if ( !s_instance )
    {
        s_instance = new SourceList();
    }

    return s_instance;
}


SourceList::SourceList( QObject* parent )
    : QObject( parent )
    , m_isReady( false )
{
}


const source_ptr&
SourceList::getLocal() const
{
    return m_local;
}


void
SourceList::setWebSource( const source_ptr& websrc )
{
    m_dummy = websrc;
}


const source_ptr
SourceList::webSource() const
{
    return m_dummy;
}


void
SourceList::loadSources()
{
    Hatchet::DatabaseCommand_LoadAllSources* cmd = new Hatchet::DatabaseCommand_LoadAllSources();

    connect( cmd, SIGNAL( done( QList<Hatchet::source_ptr> ) ),
                    SLOT( setSources( QList<Hatchet::source_ptr> ) ) );

    Database::instance()->enqueue( Hatchet::dbcmd_ptr( cmd ) );
}


void
SourceList::setSources( const QList<Hatchet::source_ptr>& sources )
{
    {
        QMutexLocker lock( &m_mut );

        m_isReady = true;
        foreach( const source_ptr& src, sources )
        {
            add( src );
        }

        tLog() << Q_FUNC_INFO << "- Total sources now:" << m_sources.size();
    }

    emit ready();
}


void
SourceList::setLocal( const Hatchet::source_ptr& localSrc )
{
    Q_ASSERT( localSrc->isLocal() );
    Q_ASSERT( m_local.isNull() );

    {
        QMutexLocker lock( &m_mut );
        m_sources.insert( localSrc->nodeId(), localSrc );
        m_local = localSrc;
    }


    connect( localSrc.data(), SIGNAL( latchedOn( Hatchet::source_ptr ) ), this, SLOT( latchedOn( Hatchet::source_ptr ) ) );
    connect( localSrc.data(), SIGNAL( latchedOff( Hatchet::source_ptr ) ), this, SLOT( latchedOff( Hatchet::source_ptr ) ) );
    emit sourceAdded( localSrc );
}


void
SourceList::add( const source_ptr& source )
{
    Q_ASSERT( m_isReady );

//    qDebug() << "Adding to sources:" << source->nodeId() << source->id();
    m_sources.insert( source->nodeId(), source );

    if ( source->id() > 0 )
        m_sources_id2name.insert( source->id(), source->nodeId() );
    connect( source.data(), SIGNAL( syncedWithDatabase() ), SLOT( sourceSynced() ) );

    collection_ptr coll( new RemoteCollection( source ) );
    coll->setWeakRef( coll.toWeakRef() );
    source->addCollection( coll );

    connect( source.data(), SIGNAL( latchedOn( Hatchet::source_ptr ) ), this, SLOT( latchedOn( Hatchet::source_ptr ) ) );
    connect( source.data(), SIGNAL( latchedOff( Hatchet::source_ptr ) ), this, SLOT( latchedOff( Hatchet::source_ptr ) ) );
    emit sourceAdded( source );
}


void
SourceList::removeAllRemote()
{
    foreach( const source_ptr& s, m_sources )
    {
        qDebug() << "Disconnecting" << s->friendlyName() << s->isLocal() << s->controlConnection() << s->isOnline();
        if ( !s->isLocal() && s->controlConnection() )
        {
            s->controlConnection()->shutdown( true );
        }
    }
}


QList<source_ptr>
SourceList::sources( bool onlyOnline ) const
{
    QMutexLocker lock( &m_mut );

    QList< source_ptr > sources;
    foreach( const source_ptr& src, m_sources )
    {
        if ( !onlyOnline || src->controlConnection() )
            sources << src;
    }

    return sources;
}


source_ptr
SourceList::get( int id ) const
{
    QMutexLocker lock( &m_mut );

    if ( id == 0 )
        return m_local;
    else
        return m_sources.value( m_sources_id2name.value( id ) );
}


source_ptr
SourceList::get( const QString& username, const QString& friendlyName, bool autoCreate )
{
    QMutexLocker lock( &m_mut );

    source_ptr source;
    if ( Database::instance()->impl()->dbid() == username )
    {
        return m_local;
    }

    if ( !m_sources.contains( username ) )
    {
        if ( autoCreate )
        {
            Q_ASSERT( !friendlyName.isEmpty() );
            source = source_ptr( new Source( -1, username ) );
            source->setDbFriendlyName( friendlyName );
            add( source );
        }
    }
    else
    {
        source = m_sources.value( username );
        source->setDbFriendlyName( friendlyName );
    }

    return source;
}


void
SourceList::createPlaylist( const Hatchet::source_ptr& src, const QVariant& contents )
{
    Hatchet::playlist_ptr p = Hatchet::playlist_ptr( new Hatchet::Playlist( src ) );
    HatchetUtils::qvariant2qobject( contents.toMap(), p.data() );
    p->reportCreated( p );
}


void
SourceList::createDynamicPlaylist( const Hatchet::source_ptr& src, const QVariant& contents )
{
    Hatchet::dynplaylist_ptr p = Hatchet::dynplaylist_ptr( new Hatchet::DynamicPlaylist( src, contents.toMap().value( "type", QString() ).toString()  ) );
    HatchetUtils::qvariant2qobject( contents.toMap(), p.data() );
    p->reportCreated( p );
}


void
SourceList::sourceSynced()
{
    Source* src = qobject_cast< Source* >( sender() );

    m_sources_id2name.insert( src->id(), src->nodeId() );
}


unsigned int
SourceList::count() const
{
    QMutexLocker lock( &m_mut );
    return m_sources.size();
}


QList<collection_ptr>
SourceList::scriptCollections() const
{
    return m_scriptCollections;
}


void
SourceList::latchedOff( const source_ptr& to )
{
    Source* s = qobject_cast< Source* >( sender() );
    const source_ptr source = m_sources[ s->nodeId() ];

    emit sourceLatchedOff( source, to );
}


void
SourceList::addScriptCollection( const collection_ptr& collection )
{
    m_scriptCollections.append( collection );

    emit scriptCollectionAdded( collection );
}


void
SourceList::removeScriptCollection( const collection_ptr& collection )
{
    emit scriptCollectionRemoved( collection );

    m_scriptCollections.removeAll( collection );
}


void
SourceList::latchedOn( const source_ptr& to )
{

    Source* s = qobject_cast< Source* >( sender() );
    const source_ptr source = m_sources[ s->nodeId() ];

    emit sourceLatchedOn( source, to );
}

