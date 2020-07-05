/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2014,      Teo Mrnjavac <teo@kde.org>
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

#ifndef HATCHETAPP_H
#define HATCHETAPP_H

#define APP HatchetApp::instance()

#include "mac/HatchetApp_Mac.h" // for PlatforInterface
#include "Typedefs.h"
#include "libhatchet-playdarapi/PlaydarApi.h"
#include "utils/HatchetUtils.h"
#include "kdsingleapplicationguard.h"

#include "HeadlessCheck.h"
#include "config.h"

#include <QRegExp>
#include <QFile>
#include <QSettings>
#include <QDir>
#include <QPersistentModelIndex>
#include <QPointer>

class AudioEngine;
class ScanManager;
class Servent;
class SipHandler;
class HatchetSettings;
class AudioControls;
class SplashWidget;

namespace Hatchet
{
    class ShortcutHandler;
    class Database;
    namespace InfoSystem
    {
        class InfoSystem;
    }

    namespace Accounts
    {
        class AccountManager;
    }
}

#ifdef HAVE_LIBLASTFM
    #include <lastfm5/NetworkAccessManager.h>
    #include "Scrobbler.h"
#endif

class HatchetWindow;


// this also acts as a a container for important top-level objects
// that other parts of the app need to find
// (eg, library, pipeline, friends list)
class HatchetApp : public HATCHET_APPLICATION, public Hatchet::PlatformInterface
{
Q_OBJECT

public:
    HatchetApp( int& argc, char *argv[] );
    virtual ~HatchetApp();

    void init();
    static HatchetApp* instance();

    AudioControls* audioControls();
    HatchetWindow* mainWindow() const;

    // PlatformInterface
    virtual bool loadUrl( const QString& url );

    // reimplemented from QApplication/QCoreApplication
    virtual bool notify( QObject* receiver, QEvent* e );

signals:
    void hatchetLoaded();

public slots:
    virtual void activate();
    void instanceStarted( KDSingleApplicationGuard::Instance );

private slots:
    void initServent();
    void initSIP();
    void initHTTP();
    void initFactoriesForAccountManager();
    void initEnergyEventHandler();

    void onShutdownDelayed();

    void spotifyApiCheckFinished();
    void onInfoSystemReady();

    void onSchemaUpdateStarted();
    void onSchemaUpdateStatus( const QString& status );
    void onSchemaUpdateDone();

    void startSplashWidget( const QString& initialMessage = QString() );
    void updateSplashWidgetMessage( const QString& message );
    void killSplashWidget();

    void playlistRemoved( const Hatchet::playlist_ptr& playlist );
    void ipDetectionFailed( QNetworkReply::NetworkError error, QString errorString );

private:
    void registerMetaTypes();

    void printHelp();

    // Start-up order: database, collection, pipeline, servent, http
    void initDatabase();
    void initLocalCollection();
    void initPipeline();

    QPointer<Hatchet::Database> m_database;
    QPointer<ScanManager> m_scanManager;
    QPointer<AudioEngine> m_audioEngine;
    QPointer<Servent> m_servent;
    QPointer<Hatchet::InfoSystem::InfoSystem> m_infoSystem;
    QPointer<Hatchet::ShortcutHandler> m_shortcutHandler;
    QPointer< Hatchet::Accounts::AccountManager > m_accountManager;
    bool m_scrubFriendlyName;
    QString m_queuedUrl;
    QFile m_logFile;

#ifdef HAVE_LIBLASTFM
    Scrobbler* m_scrobbler;
#endif

    HatchetWindow* m_mainwindow;
    QPointer<PlaydarApi> playdarApi;

    SplashWidget* m_splashWidget;

    bool m_headless;
};

Q_DECLARE_METATYPE( PairList )

#endif // HATCHETAPP_H
