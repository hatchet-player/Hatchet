/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2013,    Dominik Schmidt <domme@tomahawk-player.org>
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

#ifndef VIEWPAGELAZYLOADER_H
#define VIEWPAGELAZYLOADER_H

#include "ViewPagePlugin.h"

#include "DllMacro.h"

namespace Hatchet
{

template <class T>
class ViewPageLazyLoader : public ViewPagePlugin
{
public:
    ViewPageLazyLoader<T>()
        : m_widget( 0 )
    {
    }


    virtual ~ViewPageLazyLoader()
    {
        if ( !m_widget.isNull() )
            delete m_widget.data();
    }


    virtual T* widget()
    {
        if ( m_widget.isNull() )
            m_widget = new T();

        return m_widget.data();
    }


    virtual playlistinterface_ptr playlistInterface() const
    {
        if ( !m_widget.isNull() )
            return m_widget->playlistInterface();

        return playlistinterface_ptr();
    }


    virtual bool isBeingPlayed() const
    {
        if ( !m_widget.isNull() && m_widget->isBeingPlayed() )
            return true;

        return false;
    }


    virtual bool jumpToCurrentTrack()
    {
        if ( !m_widget.isNull() && m_widget->jumpToCurrentTrack() )
            return true;

        return false;
    }

protected:
    QPointer<T> m_widget;
};

} // ns

#endif //VIEWPAGELAZYLOADER_H
