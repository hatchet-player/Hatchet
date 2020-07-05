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

#ifndef PIPELINESTATUSITEM_H
#define PIPELINESTATUSITEM_H

#include "jobview/JobStatusItem.h"
#include "Query.h"

#include <QPixmap>
#include <QPointer>

class PipelineStatusItem : public JobStatusItem
{
    Q_OBJECT
public:
    explicit PipelineStatusItem( const Hatchet::query_ptr& q );
    virtual ~PipelineStatusItem();

    virtual QString rightColumnText() const;
    virtual QString mainText() const;
    virtual QPixmap icon() const;

    virtual QString type() const { return "pipeline"; }

    virtual bool collapseItem() const { return false; } // We can't collapse, since we use this meta-item instead of one per resolve

private slots:
    void resolving( const Hatchet::query_ptr& query );
    void idle();

private:
    QString m_latestQuery;
};

class PipelineStatusManager : public QObject
{
    Q_OBJECT
public:
    explicit PipelineStatusManager( QObject* parent = 0 );
    virtual ~PipelineStatusManager() {}

private slots:
    void resolving( const Hatchet::query_ptr& p );

private:
    QPointer<PipelineStatusItem> m_curItem;
};


#endif // PIPELINESTATUSITEM_H
