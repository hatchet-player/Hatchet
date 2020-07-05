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

#ifndef SOURCELIST_H
#define SOURCELIST_H

#include <QObject>
#include <QMutex>
#include <QMap>

#include "Typedefs.h"
#include "Source.h"

#include "DllMacro.h"

class DLLEXPORT SourceList : public QObject
{
Q_OBJECT

public:
    static SourceList* instance();

    explicit SourceList( QObject* parent = 0 );

    bool isReady() const { return m_isReady; }

    const Hatchet::source_ptr& getLocal() const;
    void setLocal( const Hatchet::source_ptr& localSrc );

    void setWebSource( const Hatchet::source_ptr& websrc );
    const Hatchet::source_ptr webSource() const;

    void loadSources();
    void removeAllRemote();

    QList<Hatchet::source_ptr> sources( bool onlyOnline = false ) const;
    unsigned int count() const;

    void addScriptCollection( const Hatchet::collection_ptr& collection );
    void removeScriptCollection( const Hatchet::collection_ptr& collection );
    QList<Hatchet::collection_ptr> scriptCollections() const;

    Hatchet::source_ptr get( const QString& username, const QString& friendlyName = QString(), bool autoCreate = false );
    Hatchet::source_ptr get( int id ) const;

public slots:
    // called by the playlist creation dbcmds
    void createPlaylist( const Hatchet::source_ptr& src, const QVariant& contents );
    void createDynamicPlaylist( const Hatchet::source_ptr& src, const QVariant& contents );

signals:
    void ready();

    void sourceAdded( const Hatchet::source_ptr& );
    void sourceRemoved( const Hatchet::source_ptr& );

    void scriptCollectionAdded( const Hatchet::collection_ptr& );
    void scriptCollectionRemoved( const Hatchet::collection_ptr& );

    void sourceLatchedOn( const Hatchet::source_ptr& from, const Hatchet::source_ptr& to );
    void sourceLatchedOff( const Hatchet::source_ptr& from, const Hatchet::source_ptr& to );

private slots:
    void setSources( const QList<Hatchet::source_ptr>& sources );
    void sourceSynced();

    void latchedOn( const Hatchet::source_ptr& );
    void latchedOff( const Hatchet::source_ptr& );

private:
    void add( const Hatchet::source_ptr& source );

    QMap< QString, Hatchet::source_ptr > m_sources;
    QMap< int, QString > m_sources_id2name;

    QList< Hatchet::collection_ptr > m_scriptCollections;

    bool m_isReady;
    Hatchet::source_ptr m_local;
    Hatchet::source_ptr m_dummy;
    mutable QMutex m_mut; // mutable so const methods can use a lock

    static SourceList* s_instance;
};

#endif // SOURCELIST_H
