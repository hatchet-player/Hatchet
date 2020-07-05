#include "AudioEngine.h"
#include "AudioOutput.h"

#include <stdint.h>

#include <QObject>
#include <QTimer>
#include <QQueue>
#include <QTemporaryFile>

class AudioEnginePrivate : public QObject
{
Q_OBJECT

public:
    AudioEnginePrivate( AudioEngine* q )
        : q_ptr ( q )
        , audioRetryCounter( 0 )
        , underrunCount( 0 )
        , underrunNotified( false )
    {
    }
    AudioEngine* q_ptr;
    Q_DECLARE_PUBLIC ( AudioEngine )


public slots:
    void onStateChanged( AudioOutput::AudioState newState, AudioOutput::AudioState oldState );

private:
    QSharedPointer<QIODevice> input;

    Hatchet::query_ptr stopAfterTrack;
    Hatchet::result_ptr currentTrack;
    Hatchet::playlistinterface_ptr playlist;
    Hatchet::playlistinterface_ptr currentTrackPlaylist;
    Hatchet::playlistinterface_ptr queue;

    AudioOutput* audioOutput;

    unsigned int timeElapsed;
    bool waitingOnNewTrack;

    AudioState state;
    QQueue< AudioState > stateQueue;
    QTimer stateQueueTimer;

    int audioRetryCounter;
    quint8 underrunCount;
    bool underrunNotified;

    QTemporaryFile* coverTempFile;

    static AudioEngine* s_instance;
};
