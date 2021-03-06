/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#pragma once
#ifndef PIPELINE_H
#define PIPELINE_H

#include "DllMacro.h"
#include "Typedefs.h"
#include "Query.h"

#include <QObject>
#include <QList>
#include <QStringList>

#include <functional>

namespace Hatchet
{

class PipelinePrivate;
class Resolver;
class ExternalResolver;
typedef std::function<Hatchet::ExternalResolver*( QString, QString, QStringList )> ResolverFactoryFunc;

class DLLEXPORT Pipeline : public QObject
{
Q_OBJECT

public:
    static Pipeline* instance();

    explicit Pipeline( QObject* parent = nullptr );
    virtual ~Pipeline();

    bool isRunning() const;

    unsigned int pendingQueryCount() const;
    unsigned int activeQueryCount() const;

    void reportError( QID qid, Hatchet::Resolver* r );
    void reportResults( QID qid, Hatchet::Resolver* r, const QList< result_ptr >& results );
    void reportAlbums( QID qid, const QList< album_ptr >& albums );
    void reportArtists( QID qid, const QList< artist_ptr >& artists );

    void addExternalResolverFactory( ResolverFactoryFunc resolverFactory );
    Hatchet::ExternalResolver* addScriptResolver( const QString& accountId, const QString& scriptPath, const QStringList& additionalScriptPaths = QStringList() );
    void stopScriptResolver( const QString& scriptPath );
    void removeScriptResolver( const QString& scriptPath );
    QList< QPointer< ExternalResolver > > scriptResolvers() const;
    Hatchet::ExternalResolver* resolverForPath( const QString& scriptPath );

    QList< Resolver* > resolvers() const;
    void addResolver( Resolver* r );
    void removeResolver( Resolver* r );

    query_ptr query( const QID& qid ) const;
    result_ptr result( const RID& rid ) const;

    bool isResolving( const query_ptr& q ) const;

public slots:
    void resolve( const query_ptr& q, bool prioritized = true, bool temporaryQuery = false );
    void resolve( const QList<query_ptr>& qlist, bool prioritized = true, bool temporaryQuery = false );
    void resolve( QID qid, bool prioritized = true, bool temporaryQuery = false );

    void start();
    void stop();
    void databaseReady();

signals:
    void running();
    void idle();
    void resolving( const Hatchet::query_ptr& query );

    void resolverAdded( Hatchet::Resolver* );
    void resolverRemoved( Hatchet::Resolver* );

protected:
    QScopedPointer<PipelinePrivate> d_ptr;

private slots:
    void timeoutShunt( const query_ptr& q, Hatchet::Resolver* r );
    void shunt( const query_ptr& q );
    void shuntNext();

    void onTemporaryQueryTimer();
    void onResultUrlCheckerDone( );

private:
    Q_DECLARE_PRIVATE( Pipeline )

    void addResultsToQuery( const query_ptr& query, const QList< result_ptr >& results );
    Hatchet::Resolver* nextResolver( const Hatchet::query_ptr& query ) const;

    void checkQIDState( const Hatchet::query_ptr& query );
    void incQIDState( const Hatchet::query_ptr& query, Hatchet::Resolver* );
    void decQIDState( const Hatchet::query_ptr& query, Hatchet::Resolver* );
};

} // Hatchet

#endif // PIPELINE_H
