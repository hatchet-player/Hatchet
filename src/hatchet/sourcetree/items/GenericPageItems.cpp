/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
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

#include "GenericPageItems.h"

#include "utils/HatchetUtils.h"
#include "utils/Logger.h"
#include "ViewManager.h"
#include "audio/AudioEngine.h"

using namespace Hatchet;


/// Generic page item
GenericPageItem::GenericPageItem( SourcesModel* model, SourceTreeItem* parent,
                                  const QString& text, const QIcon& icon,
                                  std::function< ViewPage* () > show,
                                  std::function< ViewPage* () > get )
    : SourceTreeItem( model, parent, SourcesModel::GenericPage )
    , m_icon( icon )
    , m_text( text )
    , m_sortValue( 0 )
    , m_show( show )
    , m_get( get )
{
    if ( ViewPage* p = m_get() )
        model->linkSourceItemToPage( this, p );
}


GenericPageItem::~GenericPageItem()
{
}


void
GenericPageItem::activate()
{
    ViewPage* p = m_show();
    model()->linkSourceItemToPage( this, p );
}


QString
GenericPageItem::text() const
{
    return m_text;
}


QIcon
GenericPageItem::icon() const
{
    return m_icon;
}


bool
GenericPageItem::willAcceptDrag( const QMimeData* data ) const
{
    if ( m_get() == NULL )
    {
        return false;
    }
    return m_get()->willAcceptDrag(data);
}


bool
GenericPageItem::dropMimeData( const QMimeData* data, Qt::DropAction action )
{
    if ( m_get() == NULL )
    {
        return false;
    }
    return m_get()->dropMimeData(data, action);
}


void
GenericPageItem::setText( const QString& text )
{
    m_text = text;
    emit updated();
}


bool
GenericPageItem::isBeingPlayed() const
{
    if ( m_get() )
    {
        if ( m_get()->isBeingPlayed() )
            return true;

        if ( m_get()->playlistInterface() && m_get()->playlistInterface() == AudioEngine::instance()->currentTrackPlaylist() )
            return true;

        if ( m_get()->playlistInterface() && m_get()->playlistInterface()->hasChildInterface( AudioEngine::instance()->currentTrackPlaylist() ) )
            return true;
    }

    return false;
}


void
GenericPageItem::setDeletable( bool deletable )
{
    if ( deletable )
    {
        setRowType( SourcesModel::DeletablePage );
    }
    else
    {
        setRowType( SourcesModel::GenericPage );
    }
}

void
GenericPageItem::setRemovable( bool removable )
{
    if ( removable )
    {
        setRowType( SourcesModel::RemovablePage );
    }
    else
    {
        setRowType( SourcesModel::GenericPage );
    }
}

int
GenericPageItem::peerSortValue() const
{
    return m_sortValue;
}


void
GenericPageItem::setSortValue( int value )
{
    m_sortValue = value;
}


void
GenericPageItem::removeFromList()
{
    SourceTreeItem::removeFromList();

    if ( type() == SourcesModel::DeletablePage )
        ViewManager::instance()->destroyPage( m_get() );
}
