/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2014, Uwe L. Korn <uwelk@xhochy.com>
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

#ifndef WHATSNEW_0_8_H
#define WHATSNEW_0_8_H

#include "ViewPagePlugin.h"
#include "ViewPageLazyLoader.h"

#include <QWidget>

#include "../ViewPageDllMacro.h"

class QScrollArea;

namespace Ui
{
    class WhatsNewWidget_0_8;
}

namespace Hatchet
{
namespace Widgets
{


class WhatsNewWidget_0_8 : public QWidget
{
Q_OBJECT

friend class WhatsNew_0_8;

public:
    WhatsNewWidget_0_8( QWidget* parent = 0 );
    virtual ~WhatsNewWidget_0_8();

    virtual bool isBeingPlayed() const;
    virtual playlistinterface_ptr playlistInterface() const;
    virtual bool jumpToCurrentTrack();

protected:
    void changeEvent( QEvent* e );

private slots:
    void inboxBoxClicked();
    void urlLookupBoxClicked();
    void beatsBoxClicked();
    void gmusicBoxClicked();
    void networkingBoxClicked();
    void androidBoxClicked();

private:
    void activateAnchor( QWidget* widget );

    QWidget* m_widget;
    QScrollArea* m_area;

    Ui::WhatsNewWidget_0_8 *ui;
};

const QString WHATSNEW_0_8_VIEWPAGE_NAME = "whatsnew_0_8";

class HATCHET_VIEWPAGE_EXPORT WhatsNew_0_8 : public Hatchet::ViewPageLazyLoader< WhatsNewWidget_0_8 >
{
Q_OBJECT
Q_INTERFACES( Hatchet::ViewPagePlugin )
Q_PLUGIN_METADATA( IID "org.hatchet-player.Player.ViewPagePlugin" )

public:
    WhatsNew_0_8( QWidget* parent = 0 );
    virtual ~WhatsNew_0_8();

    const QString defaultName() override { return WHATSNEW_0_8_VIEWPAGE_NAME; }
    QString title() const override { return tr( "What's new in 0.8?" ); }
    QString description() const override { return tr( "An overview of the changes and additions since 0.7." ); }
    const QString pixmapPath() const override { return ( RESPATH "images/whatsnew.svg" ); }

    bool addPageItem() const override;
    bool isRemovable() const override { return true; }
    bool isDeletable() const override { return false; }
    void onItemDeleted() override;

    int sortValue() override { return 1; }
};


} // Widgets
} // Hatchet
#endif // WHATSNEW_0_8_H
