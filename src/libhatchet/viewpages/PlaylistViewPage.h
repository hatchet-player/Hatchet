/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef PLAYLISTVIEWPAGE_H
#define PLAYLISTVIEWPAGE_H

#include "ViewPage.h"
#include "PlaylistInterface.h"
#include "DllMacro.h"

class QStackedWidget;

class ContextView;
class FilterHeader;

class DLLEXPORT PlaylistViewPage : public QWidget, public Hatchet::ViewPage
{
Q_OBJECT

public:
    explicit PlaylistViewPage( QWidget* parent = 0, QWidget* extraHeader = 0 );
    ~PlaylistViewPage();

    virtual QWidget* widget() { return this; }
    virtual Hatchet::playlistinterface_ptr playlistInterface() const;

    virtual QString title() const;
    virtual QString description() const;
    virtual QPixmap pixmap() const;

    virtual bool jumpToCurrentTrack();
    virtual bool isTemporaryPage() const;
    virtual bool isBeingPlayed() const;
    void setTemporaryPage( bool b );

    ContextView* view() const;

    void setPixmap( const QPixmap& pixmap );

public slots:
    virtual bool setFilter( const QString& pattern );

signals:
    void destroyed( QWidget* widget );

private slots:
    void onModelChanged();
    void onWidgetDestroyed( QWidget* widget );

private:
    FilterHeader* m_header;
    ContextView* m_view;
    QPixmap m_pixmap;
    bool m_temporary;
};

#endif // PLAYLISTVIEWPAGE_H
