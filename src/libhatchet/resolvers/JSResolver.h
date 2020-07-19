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

#ifndef JSRESOLVER_H
#define JSRESOLVER_H

#include "Config.h"
#include "ExternalResolverGui.h"
#include "Typedefs.h"
#include "ScriptPlugin.h"
#include "ScriptEngine.h" // hack, also should be renamed to JSEngine

#include "DllMacro.h"

namespace Hatchet
{

class ScriptInfoPlugin;
class JSResolverHelper;
class JSResolverPrivate;
class ScriptEngine;
class ScriptJob;
class ScriptObject;
class ScriptAccount;

class DLLEXPORT JSResolver : public Hatchet::ExternalResolverGui, public ScriptPlugin
{
Q_OBJECT

friend class JSResolverHelper;
friend class JSAccount;

public:
    explicit JSResolver( const QString& accountId, const QString& scriptPath, const QStringList& additionalScriptPaths = QStringList() );
    virtual ~JSResolver();
    static ExternalResolver* factory( const QString& accountId, const QString& scriptPath, const QStringList& additionalScriptPaths = QStringList() );

    Capabilities capabilities() const override;

    QString name() const override;
    QPixmap icon( const QSize& size ) const override;
    unsigned int weight() const override;
    unsigned int timeout() const override;

    AccountConfigWidget* configUI() const override;
    void saveConfig() override;

    ExternalResolver::ErrorState error() const override;
    bool running() const override;
    void reload() override;

    void setIcon( const QPixmap& icon ) override;

    bool canParseUrl( const QString& url, UrlType type ) override;

    QVariantMap loadDataFromWidgets();

    ScriptAccount* scriptAccount() const;

    ScriptJob* getStreamUrl( const result_ptr& result ) override;
    ScriptJob* getDownloadUrl( const result_ptr& result, const DownloadFormat &format ) override;


public slots:
    void resolve( const Hatchet::query_ptr& query ) override;
    void stop() override;
    void start() override;

    // For UrlLookup
    void lookupUrl( const QString& url ) override;

signals:
    void stopped();

protected:
    QVariant callOnResolver( const QString& scriptSource );

private slots:
    void onResolveRequestDone(const QVariantMap& data);
    void onLookupUrlRequestDone(const QVariantMap& data);

private:
    void init();

    void loadUi();
    void onCapabilitiesChanged( Capabilities capabilities );

    // encapsulate javascript calls
    QVariantMap resolverUserConfig();

    Q_DECLARE_PRIVATE( JSResolver )
    QScopedPointer<JSResolverPrivate> d_ptr;


// TODO: move lookupUrl stuff to its own plugin type
    QString instanceUUID();
    static Hatchet::query_ptr parseTrack( const QVariantMap& track );
    QString m_pendingUrl;
    Hatchet::album_ptr m_pendingAlbum;
private slots:
    void tracksAdded( const QList<Hatchet::query_ptr>& tracks, const Hatchet::ModelMode, const Hatchet::collection_ptr& collection );
    void pltemplateTracksLoadedForUrl( const QString& url, const Hatchet::playlisttemplate_ptr& pltemplate );
};

} // ns: Hatchet
#endif // JSRESOLVER_H
