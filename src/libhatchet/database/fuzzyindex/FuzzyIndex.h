/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
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

#ifndef FUZZYINDEX_H
#define FUZZYINDEX_H

#include <QObject>
#include <QMap>
#include <QHash>
#include <QString>
#include <QMutex>

#include <lucene++/LuceneHeaders.h>

#include "Query.h"
#include "database/commands/UpdateSearchIndex.h"

class FuzzyIndex : public QObject
{
Q_OBJECT

public:
    explicit FuzzyIndex( QObject* parent, const QString& filename, bool wipe = false );
    virtual ~FuzzyIndex();

    void beginIndexing();
    void endIndexing();
    void appendFields( const Hatchet::IndexData& data );

    /**
     * Delete the index from the harddrive.
     *
     * You should no longer use this FuzzyIndex object after this call.
     */
    void deleteIndex();

    virtual void updateIndex();

signals:
    void indexStarted();
    void indexReady();

public slots:
    void loadLuceneIndex();
    bool wipeIndex();

    QMap< int, float > search( const Hatchet::query_ptr& query );
    QMap< int, float > searchAlbum( const Hatchet::query_ptr& query );

private slots:
    void updateIndexSlot();

private:
    QMutex m_mutex;
    QString m_lucenePath;

    boost::shared_ptr<Lucene::SimpleAnalyzer> m_analyzer;
    Lucene::IndexWriterPtr m_luceneWriter;
    Lucene::IndexReaderPtr m_luceneReader;
    Lucene::FSDirectoryPtr m_luceneDir;
    Lucene::IndexSearcherPtr m_luceneSearcher;
};

#endif // FUZZYINDEX_H
