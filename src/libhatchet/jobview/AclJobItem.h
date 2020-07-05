/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2012, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef ACLJOBITEM_H
#define ACLJOBITEM_H

#include "DllMacro.h"

#include "network/acl/AclRegistry.h"
#include "jobview/JobStatusItem.h"

#include <QStyledItemDelegate>

class QListView;

class DLLEXPORT ACLJobDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ACLJobDelegate ( QObject* parent = nullptr );
    virtual ~ACLJobDelegate();

    void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;
    QSize sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const override;

    void emitSizeHintChanged( const QModelIndex &index );

signals:
    void update( const QModelIndex& idx );
    void aclResult( Hatchet::ACLStatus::Type result );

protected:
    bool editorEvent( QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index ) override;

private:
    void drawRoundedButton( QPainter* painter, const QRect& btnRect, bool red = false ) const;

    QPoint m_savedHoverPos;
    mutable QRect m_savedAcceptRect;
    mutable QRect m_savedDenyRect;
};


class DLLEXPORT ACLJobItem : public JobStatusItem
{
    Q_OBJECT
public:
    explicit ACLJobItem( ACLRegistry::User user, const QString &username );
    virtual ~ACLJobItem();

    int weight() const override { return 99; }
    
    QString rightColumnText() const override { return QString(); }
    QString mainText() const override { return QString(); }
    QPixmap icon() const override { return QPixmap(); }
    QString type() const override { return "acljob"; }

    int concurrentJobLimit() const override { return 3; }

    bool hasCustomDelegate() const override { return true; }
    void createDelegate( QObject* parent = nullptr ) override;
    QStyledItemDelegate* customDelegate() const override { return m_delegate; }

    ACLRegistry::User user() const { return m_user; }
    const QString& username() const { return m_username; }
    
signals:
    void userDecision( ACLRegistry::User user );

public slots:
    void aclResult( Hatchet::ACLStatus::Type result );
    
private:
    QStyledItemDelegate* m_delegate;
    ACLRegistry::User m_user;
    const QString m_username;
};

#endif // ACLJOBITEM_H
