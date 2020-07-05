#include "database/Database.h"
#include "database/DatabaseCommand_Resolve.h"
#include "utils/HatchetUtils.h"
#include "HatchetVersion.h"
#include "Typedefs.h"

#include <QCoreApplication>
#include <QDir>

#include <chrono>
#include <iostream>


class Tasks: public QObject
{
Q_OBJECT
public:
    Q_INVOKABLE void startDatabase( QString dbpath )
    {
        database = QSharedPointer<Hatchet::Database>( new Hatchet::Database( dbpath ) );
        connect( database.data(), SIGNAL( ready() ), SLOT( runCmd() ), Qt::QueuedConnection );
        database->loadIndex();
    }

    Hatchet::dbcmd_ptr cmd;
    QSharedPointer<Hatchet::Database> database;
    Hatchet::query_ptr query;

    // Time measurements
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point resolveDoneTime;

public slots:
    void runCmd()
    {
        database->enqueue( cmd );
        startTime = std::chrono::high_resolution_clock::now();
    }

    void onResults( const Hatchet::QID, const QList< Hatchet::result_ptr>& results )
    {
        resolveDoneTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration =
                std::chrono::duration_cast<std::chrono::duration<double>>( resolveDoneTime - startTime );

        std::cerr << "Fulltext query took " << duration.count()
                  << "s and returned " << results.length() << " results."
                  << std::endl;

        // Query is destructed by deleteLater() so we need to wait for the
        // event queue to process it.
        connect( query.data(), SIGNAL( destroyed( QObject* ) ),
                 thread(), SLOT( quit() ) );

        // Remove references to local objects, so they are queued for destruction.
        cmd.clear();
        query.clear();
    }
};

// Include needs to go here as Tasks needs to be defined before.
#include "fuzzysearch.moc"

int main( int argc, char* argv[] )
{
    QCoreApplication app( argc, argv );
    // TODO: Add an argument to change the path
    app.setOrganizationName( HATCHET_ORGANIZATION_NAME );

    qRegisterMetaType< QList< Hatchet::result_ptr > >();
    qRegisterMetaType< Hatchet::QID >("Hatchet::QID");

    // Helper QObject to connect slots and actions in the correct thread.
    Tasks tasks;

    // Start a thread so we can actually block main until the end of the DbCmd
    QThread thread( nullptr );
    thread.start();

    // We need to do this or the finished() signal/quit() SLOT is not called.
    thread.moveToThread( &thread );
    tasks.moveToThread( &thread );

    // Load the Database
    tasks.query = Hatchet::Query::get( "Bloc Party", QString() );
    tasks.query->moveToThread( &thread );
    Hatchet::DatabaseCommand_Resolve* cmd = new Hatchet::DatabaseCommand_Resolve( tasks.query );
    tasks.cmd = Hatchet::dbcmd_ptr( cmd );
    tasks.cmd->moveToThread( &thread );
    QObject::connect( cmd, SIGNAL( results( Hatchet::QID, QList<Hatchet::result_ptr> ) ),
                      &tasks, SLOT( onResults(Hatchet::QID, QList<Hatchet::result_ptr>) ),
                      Qt::QueuedConnection );
    QString dbpath = HatchetUtils::appDataDir().absoluteFilePath( "hatchet.db" );
    QMetaObject::invokeMethod( &tasks, "startDatabase", Qt::QueuedConnection, Q_ARG( QString, dbpath ) );

    // Wait until the dbcmd was executed.
    thread.wait();
}

