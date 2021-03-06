/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2014, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2012, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2010-2011, Jeff Mitchell <jeff@tomahawk-player.org>
 *   Copyright 2012,      Teo Mrnjavac <teo@kde.org>
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

#ifndef HATCHETWINDOW_H
#define HATCHETWINDOW_H

#include "Result.h"
#include "audio/AudioEngine.h"
#include "utils/XspfLoader.h"
#include "utils/DpiScaler.h"

#include "Config.h"

#include <QMainWindow>
#include <QVariantMap>
#include <QPushButton>
#include <QString>
#include <QStackedWidget>
#include <QToolButton>
#ifdef Q_OS_WIN
    #include <shobjidl.h>
    #include <QWinThumbnailToolBar>
    #include <QWinThumbnailToolButton>
#endif

namespace Hatchet
{
    namespace Accounts
    {
        class Account;
    }
}

class JobStatusSortModel;
class QSearchField;
class SourceTreeView;
class QAction;

class SettingsDialog;
class MusicScanner;
class AudioControls;
class HatchetTrayIcon;
class PlaylistModel;
class AnimatedSplitter;
class AccountsToolButton;

namespace Ui
{
    class HatchetWindow;
    class GlobalSearchWidget;
}

class HatchetWindow : public QMainWindow, private HatchetUtils::DpiScaler
{
Q_OBJECT

public:
    HatchetWindow( QWidget* parent = 0 );
    ~HatchetWindow();

    AudioControls* audioControls();
    SourceTreeView* sourceTreeView() const;

    void setWindowTitle( const QString& title );

protected:
    void changeEvent( QEvent* e );
    void closeEvent( QCloseEvent* e );
    void showEvent( QShowEvent* e );
    void hideEvent( QHideEvent* e );
    void keyPressEvent( QKeyEvent* e );

    bool eventFilter( QObject* obj, QEvent* event );

public slots:
    void createStation();
    void createPlaylist();
    void loadPlaylist();
    void showSettingsDialog();
    void showDiagnosticsDialog();
    void legalInfo();
    void getSupport();
    void helpTranslate();
    void reportBug();
    void openLogfile();
    void updateCollectionManually();
    void rescanCollectionManually();
    void showOfflineSources();

    void fullScreenEntered();
    void fullScreenExited();

signals:
    void searchEdited( const QString& text );

private slots:
    void onHistoryBackAvailable( bool avail );
    void onHistoryForwardAvailable( bool avail );

    void onAudioEngineError( AudioEngine::AudioErrorCode error );

    void onXSPFError( XSPFLoader::XSPFErrorCode error );
    void onJSPFError();
    void onNewPlaylistOk( const Hatchet::playlist_ptr& );

    void onPlaybackLoading( const Hatchet::result_ptr result );

    void audioStarted();
    void audioFinished();
    void audioPaused();
    void audioStopped();

    void showAboutHatchet();
    void showWhatsNew_0_8();
    void checkForUpdates();

    void onSearch( const QString& search );
    void onFilterEdited();

    void loadPlaylistFinished( int );

    void minimize();
    void maximize();
    void toggleFullscreen();

    void crashNow();

    void toggleMenuBar();
    void balanceToolbar();

    void toggleLoved();

    void audioStateChanged( AudioState newState, AudioState oldState );
    
#ifdef Q_OS_WIN
    void updateWindowsLoveButton();
    void updatePreview();
#endif

private:
    void loadSettings();
    void saveSettings();

    void applyPlatformTweaks();
    void setupSignals();
    void setupMenuBar();
    void setupToolBar();
    void setupSideBar();
    void setupStatusBar();
    void setupShortcuts();
    void setupUpdateCheck();

    void importPlaylist( const QString& url, bool autoUpdate );

#ifdef Q_OS_WIN
    void setupWindowsButtons();
    QIcon thumbIcon(HatchetUtils::ImageType type);
    QWinThumbnailToolBar *m_taskbarList;
    enum TB_STATES{ TP_PREVIOUS = 0,TP_PLAY_PAUSE = 1,TP_NEXT = 2, TP_SPACE = 3, TP_LOVE = 4 };
#endif

    Ui::HatchetWindow* ui;
    QPointer<SettingsDialog> m_settingsDialog;
    QSearchField* m_searchWidget;
    AudioControls* m_audioControls;
    HatchetTrayIcon* m_trayIcon;
    SourceTreeView* m_sourcetree;
    QPushButton* m_statusButton;
    AnimatedSplitter* m_sidebar;
    JobStatusSortModel* m_jobsModel;

    // Menus and menu actions: Accounts menu
    QMenuBar    *m_menuBar;
#ifndef Q_OS_MAC
    QAction     *m_compactMenuAction;
    QMenu       *m_compactMainMenu;
#endif
    AccountsToolButton *m_accountsButton;
    QToolBar *m_toolbar;
    QWidget *m_toolbarLeftBalancer;
    QWidget *m_toolbarRightBalancer;

    QAction* m_backAction;
    QAction* m_forwardAction;

    Hatchet::result_ptr m_currentTrack;
    QString m_windowTitle;
};

#endif // HATCHETWINDOW_H
