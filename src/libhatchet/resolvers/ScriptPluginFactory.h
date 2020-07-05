/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2015, Dominik Schmidt <domme@tomahawk-player.org>
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
#ifndef HATCHET_SCRIPTPLUGINFACTORY_H
#define HATCHET_SCRIPTPLUGINFACTORY_H

#include "../Typedefs.h"
#include "ScriptPlugin.h"
#include "ScriptAccount.h"

namespace Hatchet
{

class ScriptAccount;
class ScriptCollection;

template <class T>
class ScriptPluginFactory
{
public:
    void registerPlugin( const scriptobject_ptr& object, ScriptAccount* scriptAccount )
    {
        if ( !m_scriptPlugins.value( object->id() ).isNull() )
            return;

        QSharedPointer< T > scriptPlugin = createPlugin( object, scriptAccount );
        if ( !scriptPlugin.isNull() )
        {
            m_scriptPlugins.insert( object->id(), scriptPlugin );

            if( !scriptAccount->isStopped() )
            {
                addPlugin( scriptPlugin );
            }
        }
    }


    void unregisterPlugin( const scriptobject_ptr& object )
    {
        QSharedPointer< T > scriptPlugin = m_scriptPlugins.value( object->id() );
        if ( !scriptPlugin.isNull() )
        {
            removePlugin( scriptPlugin );
        }

        m_scriptPlugins.remove( object->id() );
    }


    virtual QSharedPointer<T> createPlugin( const scriptobject_ptr&, ScriptAccount* )
    {
        return QSharedPointer<T>();
    }


    void addAllPlugins() const
    {
        foreach( const QWeakPointer< T >& scriptPlugin, m_scriptPlugins.values() )
        {
            addPlugin( scriptPlugin );
        }
    }

    virtual void addPlugin( const QSharedPointer< T >& scriptPlugin ) const
    {
    }


    void removeAllPlugins() const
    {
        foreach( const QWeakPointer< T >& scriptPlugin, m_scriptPlugins.values() )
        {
            removePlugin( scriptPlugin );
        }
    }


    virtual void removePlugin( const QSharedPointer<T>& scriptPlugin ) const
    {
    }


    const QHash< QString, QSharedPointer< T > > scriptPlugins() const
    {
        return m_scriptPlugins;
    }

private:
    QHash< QString, QSharedPointer< T > > m_scriptPlugins;
};

} // ns: Hatchet

#endif // HATCHET_SCRIPTPLUGINFACTORY_H
