/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2011,      Leo Franchi <lfranchi@kde.org>
 *   Copyright 2014,      Dominik Schmidt <domme@tomahawk-player.org>
 *   Copyright 2015-2016, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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
#ifndef HATCHET_SCRIPTACCOUNT_H
#define HATCHET_SCRIPTACCOUNT_H

#include "../Typedefs.h"

#include <QObject>
#include <QVariantMap>

//TODO: pimple
#include "../utils/WeakObjectHash.h"
#include "ScriptCollection.h"
#include <QHash>
#include <QPixmap>

#include "../DllMacro.h"

namespace Hatchet {

class ScriptObject;
class ScriptJob;
class ScriptCollectionFactory;
class ScriptInfoPluginFactory;

class DLLEXPORT ScriptAccount : public QObject
{
    Q_OBJECT

public:
    ScriptAccount( const QString& name );
    virtual ~ScriptAccount();

    void start();
    void stop();

    bool isStopped();

    QString name() const;

    void setIcon( const QPixmap& icon );
    QPixmap icon() const;

    void setFilePath( const QString& filePath );
    QString filePath() const;

    ScriptJob* invoke( const scriptobject_ptr& scriptObject, const QString& methodName, const QVariantMap& arguments );
    virtual QVariant syncInvoke( const scriptobject_ptr& scriptObject, const QString& methodName, const QVariantMap& arguments ) = 0;
    virtual void startJob( ScriptJob* scriptJob ) = 0;

    void reportScriptJobResult( const QVariantMap& result );
    void registerScriptPlugin( const QString& type, const QString& objectId );
    void unregisterScriptPlugin( const QString& type, const QString& objectId );

    virtual void reportNativeScriptJobResult( int resultId, const QVariantMap& result ) = 0;
    virtual void reportNativeScriptJobError( int resultId, const QVariantMap& error ) = 0;

    virtual void scriptPluginFactory( const QString& type, const scriptobject_ptr& object );

    virtual void showDebugger();

    // helpers
    QList< Hatchet::artist_ptr > parseArtistVariantList( const QVariantList& artistList );
    QList< Hatchet::album_ptr > parseAlbumVariantList( const QVariantList& albumList );
    QList< Hatchet::result_ptr > parseResultVariantList( const QVariantList& reslist );
    ScriptJob* resolve( const scriptobject_ptr& scriptObject, const query_ptr& query, const QString& resolveType );

private slots:
    void onJobDeleted( const QString& jobId );

    void onScriptObjectDeleted();

private: // TODO: pimple, might be renamed before tho
    QString m_name;
    QPixmap m_icon;
    QString m_filePath;
    bool m_stopped;
    QHash< QString, ScriptJob* > m_jobs;
    QHash< QString, scriptobject_ptr > m_objects;

    // port to QScopedPointer when pimple'd
    ScriptCollectionFactory* m_collectionFactory;
    ScriptInfoPluginFactory* m_infoPluginFactory;
};

} // ns: Hatchet

#endif // HATCHET_SCRIPTACCOUNT_H
