#include "database/Database.h"
#include "database/DatabaseCommand_AllArtists.h"
#include "utils/HatchetUtils.h"
#include "HatchetVersion.h"
#include "Typedefs.h"

#include <QCoreApplication>
#include <QDir>

#include <iostream>


class Tasks: public QObject
{
Q_OBJECT
public:
    Q_INVOKABLE void startDatabase( QString dbpath )
    {
        database = QSharedPointer<Hatchet::Database>( new Hatchet::Database( dbpath ) );
        connect( database.data(), SIGNAL( ready() ), SLOT( runDbCmd() ), Qt::QueuedConnection );
        database->loadIndex();
    }

    Hatchet::dbcmd_ptr cmd;
    QSharedPointer<Hatchet::Database> database;

public slots:
    void runDbCmd()
    {
        database->enqueue( cmd );
    }

    void dbCmdDone( const QList<Hatchet::artist_ptr>& artists )
    {
        std::cout << "=== ARTISTS - START ===" << std::endl;
        foreach ( const Hatchet::artist_ptr& artist, artists )
        {
            std::cout << artist->name().toStdString() << std::endl;
        }
        std::cout << "=== ARTISTS - END ===" << std::endl;
        QMetaObject::invokeMethod( thread(), "quit", Qt::QueuedConnection );
    }
};

// Include needs to go here as Tasks needs to be defined before.
#include "listartists.moc"

int main( int argc, char* argv[] )
{
    QCoreApplication app( argc, argv );
    // TODO: Add an argument to change the path
    app.setOrganizationName( HATCHET_ORGANIZATION_NAME );

    // Helper QObject to connect slots and actions in the correct thread.
    Tasks tasks;

    // Start a thread so we can actually block main until the end of the DbCmd
    QThread thread( nullptr );
    thread.start();

    // We need to do this or the finished() signal/quit() SLOT is not called.
    thread.moveToThread( &thread );
    tasks.moveToThread( &thread );

    // Load the Database
    Hatchet::DatabaseCommand_AllArtists* cmd = new Hatchet::DatabaseCommand_AllArtists();
    tasks.cmd = Hatchet::dbcmd_ptr( cmd );
    tasks.cmd->moveToThread( &thread );
    qRegisterMetaType< QList< Hatchet::artist_ptr > >();
    QObject::connect( cmd, SIGNAL( artists( QList<Hatchet::artist_ptr>  ) ),
                      &tasks, SLOT( dbCmdDone( QList<Hatchet::artist_ptr> ) ),
                      Qt::QueuedConnection );
    QString dbpath = HatchetUtils::appDataDir().absoluteFilePath( "hatchet.db" );
    QMetaObject::invokeMethod( &tasks, "startDatabase", Qt::QueuedConnection, Q_ARG( QString, dbpath ) );

    // Wait until the dbcmd was executed.
    thread.wait();
}
