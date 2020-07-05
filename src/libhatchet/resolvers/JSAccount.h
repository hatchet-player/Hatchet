/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2014, Dominik Schmidt <domme@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TOMAHAWK_JSACCOUNT_H
#define TOMAHAWK_JSACCOUNT_H


#include "ScriptAccount.h"

#include <QVariantMap>
#include <QObject>

//TODO: pimple
#include <memory>

#include "DllMacro.h"

namespace Tomahawk
{
//TODO: pimple
class ScriptEngine;
class JSResolver;

class DLLEXPORT JSAccount : public ScriptAccount
{
    Q_OBJECT

public:
    JSAccount( const QString& name );

    void startJob( ScriptJob* scriptJob ) override;
    QVariant syncInvoke( const scriptobject_ptr& scriptObject, const QString& methodName, const QVariantMap& arguments ) override;

    /**
    *  Evaluate JavaScript on the WebKit thread
    */
    Q_INVOKABLE void evaluateJavaScript( const QString& scriptSource );

    /**
    * This method must be called from the WebKit thread
    */
    QVariant evaluateJavaScriptWithResult( const QString& scriptSource );

    /**
    * Escape \ and ' in strings so they are safe to use in JavaScript
    */
    static QString escape( const QString& source );


    void loadScript( const QString& path );
    void loadScripts( const QStringList& paths );
    void addToJavaScriptWindowObject( const QString& name, QObject* object );

    void setResolver( JSResolver* resolver );
    void scriptPluginFactory( const QString& type, const scriptobject_ptr& object ) override;

    void showDebugger() override;

    static QString serializeQVariantMap(const QVariantMap& map);

    void reportNativeScriptJobResult( int resultId, const QVariantMap& result ) override;
    void reportNativeScriptJobError( int resultId, const QVariantMap& error ) override;

private:
    /**
        * Wrap the pure evaluateJavaScript call in here, while the threadings guards are in public methods
        */
    QVariant evaluateJavaScriptInternal( const QString& scriptSource );

    ScriptEngine* m_engine;
    // HACK: the order of initializen is flawed, tbr
    JSResolver* m_resolver;
};

}

#endif // TOMAHAWK_JSACCOUNT_H

