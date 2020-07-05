/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2012, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2012, Teo Mrnjavac <teo@kde.org>
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

#ifndef SOCIALWIDGET_H
#define SOCIALWIDGET_H

#include "Query.h"

#include "utils/ShortLinkHelper.h"

#include <QWidget>
#include <QAbstractItemView>
#include <QTimer>

namespace Ui
{
    class SocialWidget;
}

class SocialWidget : public QWidget
{
Q_OBJECT

public:
    SocialWidget( QWidget* parent );
    ~SocialWidget();

    Hatchet::query_ptr query() const;
    void setQuery( const Hatchet::query_ptr& query );

    QPoint position() const;
    void setPosition( QPoint position );

    bool shown() const;
    void close();

signals:
    void hidden();

public slots:
    void show( int timeoutSecs = 0 );
    void hide();

protected:
//    void changeEvent( QEvent* e );
    void paintEvent( QPaintEvent* event );
    bool eventFilter( QObject* object, QEvent* event );

private slots:
    void accept();
    void onChanged();
    void onQueryLinkReady( const QVariantMap& data );
    void onShortLinkReady( const QUrl& longUrl, const QUrl& shortUrl, const QVariant& callbackObj );

    void onGeometryUpdate();

private:
    unsigned int charsAvailable() const;

    Ui::SocialWidget* ui;

    Hatchet::query_ptr m_query;

    QPoint m_position;

    QWidget* m_parent;
    QRect m_parentRect;
    QTimer m_timer;
    Hatchet::Utils::ShortLinkHelper m_slh;
};

#endif // SOCIALWIDGET_H
