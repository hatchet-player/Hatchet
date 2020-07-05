/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2015, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2016, Dominik Schmidt <domme@tomahawk-player.org>
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

#ifndef DOWNLOADBUTTON_H
#define DOWNLOADBUTTON_H

#include "DropDownButton.h"
#include "playlist/PlayableProxyModel.h"

#include "Typedefs.h"
#include "DllMacro.h"

class DLLEXPORT DownloadButton : public DropDownButton
{
Q_OBJECT

public:
    explicit DownloadButton( const Hatchet::query_ptr& query, QWidget* parent = nullptr, QAbstractItemView* view = nullptr, const QModelIndex& index = QModelIndex() );
    explicit DownloadButton( QWidget* parent = nullptr );
    virtual ~DownloadButton();

    void setQuery( const Hatchet::query_ptr& query );

    static bool drawPrimitive( QPainter* p, const QRect& rect, const Hatchet::query_ptr& query, bool hovering );
    static bool handleEditorEvent( QEvent* event, QAbstractItemView* view, PlayableProxyModel* model, const QModelIndex& index );
    static QWidget* handleCreateEditor( QWidget* parent, const Hatchet::query_ptr& query , QAbstractItemView* view, const QModelIndex& index );

protected:
    void paintEvent( QPaintEvent* event );

private slots:
    void addDownloadJob();

private:
    static bool handleClickPreDownload( const Hatchet::query_ptr& query );
    static bool handleClickPostDownload( const Hatchet::query_ptr& query );
    void init();

    Hatchet::query_ptr m_query;
    Hatchet::result_ptr m_result;
    QAbstractItemView* m_view;
    QModelIndex m_index;
};

#endif // DOWNLOADBUTTON_H
