#ifndef QUERY_P_H
#define QUERY_P_H

#include "Query.h"

#include <QMutex>
#include <map>

namespace Hatchet
{

class QueryPrivate
{
public:
    QueryPrivate( Query* q )
        : q_ptr( q )
    {
    }

    QueryPrivate( Query* q, const track_ptr& track, const QID& _qid )
        : q_ptr( q )
        , allowReresolve( true )
        , qid( _qid )
        , queryTrack( track )
    {
    }

    QueryPrivate( Query* q, const QString& query, const QID& _qid )
        : q_ptr( q )
        , allowReresolve( true )
        , qid( _qid )
        , fullTextQuery( query )
    {
    }

    Q_DECLARE_PUBLIC( Query )
    Query* q_ptr;

private:
    QList< Hatchet::artist_ptr > artists;
    QList< Hatchet::album_ptr > albums;
    QList< Hatchet::result_ptr > results;
    Hatchet::result_ptr preferredResult;

    float score;
    bool solved;
    bool playable;
    bool resolveFinished;
    bool allowReresolve;
    mutable QID qid;

    QString fullTextQuery;

    QString resultHint;
    bool saveResultHint;

    QList< QPointer< Hatchet::Resolver > > resolvers;

    track_ptr queryTrack;

    mutable QMutex mutex;
    QWeakPointer< Hatchet::Query > ownRef;

    std::map<QString, float> howSimilarCache;
};

} // Hatchet

#endif // QUERY_P_H
