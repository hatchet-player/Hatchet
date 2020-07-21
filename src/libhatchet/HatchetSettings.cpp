/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2015, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011  Leo Franchi <lfranchi@kde.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
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

#include "HatchetSettings.h"

#include "collection/Collection.h"
#include "database/commands/UpdateSearchIndex.h"
#include "database/Database.h"
#include "database/fuzzyindex/DatabaseFuzzyIndex.h"
#include "infosystem/InfoSystemCache.h"
#include "playlist/PlaylistUpdaterInterface.h"
#include "utils/Logger.h"
#include "utils/Json.h"
#include "utils/HatchetUtils.h"

#include "PlaylistEntry.h"
#include "PlaylistInterface.h"
#include "Source.h"

#include <qt5keychain/keychain.h>
#include <QStandardPaths>
#include <QDir>

using namespace Hatchet;

HatchetSettings* HatchetSettings::s_instance = 0;


inline QDataStream&
operator<<(QDataStream& out, const SerializedUpdaters& updaters)
{
    out <<  HATCHET_SETTINGS_VERSION;
    out << (quint32)updaters.count();
    SerializedUpdaters::const_iterator iter = updaters.begin();
    int count = 0;
    for ( ; iter != updaters.end(); ++iter )
    {
        out << iter.key() << iter->type << iter->customData;
        count++;
    }
    Q_ASSERT( count == updaters.count() );
    return out;
}


inline QDataStream&
operator>>(QDataStream& in, SerializedUpdaters& updaters)
{
    quint32 count = 0, version = 0;
    in >> version;
    in >> count;

    for ( uint i = 0; i < count; i++ )
    {
        QString key, type;
        QVariantHash customData;
        in >> key;
        in >> type;
        in >> customData;
        updaters.insert( key, SerializedUpdater( type, customData ) );
    }

    return in;
}


HatchetSettings*
HatchetSettings::instance()
{
    return s_instance;
}


HatchetSettings::HatchetSettings( QObject* parent )
    : QSettings( parent )
{
    s_instance = this;

    #if !(defined(Q_OS_MAC) && defined(Q_OS_WIN))
        QFile file( fileName() );
        file.setPermissions( file.permissions() & ~( QFile::ReadGroup | QFile::WriteGroup | QFile::ExeGroup | QFile::ReadOther | QFile::WriteOther | QFile::ExeOther ) );
    #endif

    if ( !contains( "configversion" ) )
    {
        setValue( "configversion", HATCHET_SETTINGS_VERSION );
        doInitialSetup();
    }
    else if ( value( "configversion" ).toUInt() != HATCHET_SETTINGS_VERSION )
    {
        qDebug() << "Config version outdated, old:" << value( "configversion" ).toUInt()
                 << "new:" << HATCHET_SETTINGS_VERSION
                 << "Doing upgrade, if any, and backing up";

//         QString newname = QString( "%1.v%2" ).arg( dbname ).arg( version );
        if ( format() == IniFormat ||
             ( format() == NativeFormat
#ifdef Q_OS_WIN
               && false
#endif
             ) )
        {
            qDebug() << "Backing up old ini-style config file";
            const QString path = fileName();
            const QString newname = path + QString( ".v%1" ).arg( value( "configversion" ).toString() );
            QFile::copy( path, newname );

        }
        int current = value( "configversion" ).toUInt();
        while ( current < HATCHET_SETTINGS_VERSION )
        {
            doUpgrade( current, current + 1 );

            current++;
        }
        // insert upgrade code here as required
        setValue( "configversion", HATCHET_SETTINGS_VERSION );
    }

    // Ensure last.fm and spotify accounts always exist
    QString spotifyAcct, lastfmAcct;
    foreach ( const QString& acct, value( "accounts/allaccounts" ).toStringList() )
    {
        if ( acct.startsWith( "lastfmaccount_" ) )
            lastfmAcct = acct;
        else if ( acct.startsWith( "spotifyaccount_" ) )
            spotifyAcct = acct;
    }

    if ( spotifyAcct.isEmpty() )
        createSpotifyAccount();
    if ( lastfmAcct.isEmpty() )
        createLastFmAccount();
}


HatchetSettings::~HatchetSettings()
{
    s_instance = 0;
}


void
HatchetSettings::doInitialSetup()
{
    // by default we add a local network resolver
    addAccount( "sipzeroconf_autocreated" );

    createLastFmAccount();
    createSpotifyAccount();
}


void
HatchetSettings::createLastFmAccount()
{
    // Add a last.fm account for scrobbling and infosystem
    const QString accountKey = QString( "lastfmaccount_%1" ).arg( QUuid::createUuid().toString().mid( 1, 8 ) );
    addAccount( accountKey );

    beginGroup( "accounts/" + accountKey );
    setValue( "enabled", false );
    setValue( "autoconnect", true );
    setValue( "types", QStringList() << "ResolverType" << "StatusPushType" );
    endGroup();

    QStringList allAccounts = value( "accounts/allaccounts" ).toStringList();
    allAccounts << accountKey;
    setValue( "accounts/allaccounts", allAccounts );
}


void
HatchetSettings::createSpotifyAccount()
{
    const QString accountKey = QString( "spotifyaccount_%1" ).arg( QUuid::createUuid().toString().mid( 1, 8 ) );
    beginGroup( "accounts/" + accountKey );
    setValue( "enabled", false );
    setValue( "types", QStringList() << "ResolverType" );
    setValue( "configuration", QVariantHash() );
    setValue( "accountfriendlyname", "Spotify" );
    endGroup();

    QStringList allAccounts = value( "accounts/allaccounts" ).toStringList();
    allAccounts << accountKey;
    setValue( "accounts/allaccounts", allAccounts );
}


void
HatchetSettings::doUpgrade( int oldVersion, int newVersion )
{
    Q_UNUSED( newVersion );
}


void
HatchetSettings::setAcceptedLegalWarning( bool accept )
{
    setValue( "acceptedLegalWarning", accept );
}


bool
HatchetSettings::acceptedLegalWarning() const
{
    return value( "acceptedLegalWarning", false ).toBool();
}


void
HatchetSettings::setInfoSystemCacheVersion( uint version )
{
    setValue( "infosystemcacheversion", version );
}


uint
HatchetSettings::infoSystemCacheVersion() const
{
    return value( "infosystemcacheversion", 0 ).toUInt();
}


void
HatchetSettings::setGenericCacheVersion( uint version )
{
    setValue( "genericcacheversion", version );
}


uint
HatchetSettings::genericCacheVersion() const
{
    return value( "genericcacheversion", 0 ).toUInt();
}


QString
HatchetSettings::storageCacheLocation() const
{
    return QStandardPaths::writableLocation( QStandardPaths::CacheLocation );
}


QStringList
HatchetSettings::scannerPaths() const
{
    QString musicLocation;

    musicLocation = QStandardPaths::writableLocation( QStandardPaths::MusicLocation );

    return value( "scanner/paths", musicLocation ).toStringList();
}


void
HatchetSettings::setScannerPaths( const QStringList& paths )
{
    setValue( "scanner/paths", paths );
}


bool
HatchetSettings::hasScannerPaths() const
{
    //FIXME: After enough time, remove this hack
    return contains( "scanner/paths" ) || contains( "scannerpath" ) || contains( "scannerpaths" );
}


uint
HatchetSettings::scannerTime() const
{
    return value( "scanner/intervaltime", 60 ).toUInt();
}


void
HatchetSettings::setScannerTime( uint time )
{
    setValue( "scanner/intervaltime", time );
}


bool
HatchetSettings::watchForChanges() const
{
    return value( "scanner/watchforchanges", false ).toBool();
}


void
HatchetSettings::setWatchForChanges( bool watch )
{
    setValue( "scanner/watchforchanges", watch );
}


QString
HatchetSettings::downloadsPreferredFormat() const
{
    return value( "downloadmanager/preferredFormat", "MP3" ).toString();
}


void
HatchetSettings::setDownloadsPreferredFormat( const QString& format )
{
    setValue( "downloadmanager/preferredFormat", format );
}


QString
HatchetSettings::downloadsPath() const
{
    QString musicLocation;
    if ( !scannerPaths().isEmpty() )
        musicLocation = scannerPaths().first();

    return value( "downloadmanager/path", musicLocation ).toString();
}


void
HatchetSettings::setDownloadsPath( const QString& path )
{
    setValue( "downloadmanager/path", path );
}


QVariantList
HatchetSettings::downloadStates() const
{
    return value( "downloadmanager/states", QVariantList() ).toList();
}


void
HatchetSettings::setDownloadStates( const QVariantList& downloads )
{
    setValue( "downloadmanager/states", downloads );
}


bool
HatchetSettings::httpEnabled() const
{
    return value( "network/http", true ).toBool();
}


void
HatchetSettings::setHttpEnabled( bool enable )
{
    setValue( "network/http", enable );
}


bool
HatchetSettings::httpBindAll() const
{
    return value ( "network/httpbindall", false ).toBool();
}


void
HatchetSettings::setHttpBindAll( bool bindAll )
{
    setValue( "network/httpbindall", bindAll );
}


bool
HatchetSettings::crashReporterEnabled() const
{
    return value( "ui/crashReporter", true ).toBool();
}


void
HatchetSettings::setCrashReporterEnabled( bool enable )
{
    setValue( "ui/crashReporter", enable );
}


bool
HatchetSettings::songChangeNotificationEnabled() const
{
    return value( "ui/songChangeNotification", true ).toBool();
}


void
HatchetSettings::setSongChangeNotificationEnabled(bool enable)
{
    setValue( "ui/songChangeNotification", enable );
}


bool
HatchetSettings::autoDetectExternalIp() const
{
    return value( "network/auto-detect-external-ip" ).toBool();
}


void
HatchetSettings::setAutoDetectExternalIp( bool autoDetect )
{
    setValue( "network/auto-detect-external-ip", autoDetect );
}


unsigned int
HatchetSettings::volume() const
{
    return value( "audio/volume", 75 ).toUInt();
}


void
HatchetSettings::setVolume( unsigned int volume )
{
    setValue( "audio/volume", volume );
}


bool
HatchetSettings::muted() const
{
    return value( "audio/muted" ).toBool();
}


void
HatchetSettings::setMuted( bool muted )
{
    setValue( "audio/muted", muted );
}


QString
HatchetSettings::proxyHost() const
{
    return value( "network/proxy/host", QString() ).toString();
}


void
HatchetSettings::setProxyHost( const QString& host )
{
    setValue( "network/proxy/host", host );
}


QString
HatchetSettings::proxyNoProxyHosts() const
{
    return value( "network/proxy/noproxyhosts", QString() ).toString();
}


void
HatchetSettings::setProxyNoProxyHosts( const QString& hosts )
{
    setValue( "network/proxy/noproxyhosts", hosts );
}


qulonglong
HatchetSettings::proxyPort() const
{
    return value( "network/proxy/port", 1080 ).toULongLong();
}


void
HatchetSettings::setProxyPort( const qulonglong port )
{
    setValue( "network/proxy/port", port );
}


QString
HatchetSettings::proxyUsername() const
{
    return value( "network/proxy/username", QString() ).toString();
}


void
HatchetSettings::setProxyUsername( const QString& username )
{
    setValue( "network/proxy/username", username );
}


QString
HatchetSettings::proxyPassword() const
{
    return value( "network/proxy/password", QString() ).toString();
}


void
HatchetSettings::setProxyPassword( const QString& password )
{
    setValue( "network/proxy/password", password );
}


QNetworkProxy::ProxyType
HatchetSettings::proxyType() const
{
    return static_cast< QNetworkProxy::ProxyType>( value( "network/proxy/type", QNetworkProxy::NoProxy ).toInt() );
}


void
HatchetSettings::setProxyType( const QNetworkProxy::ProxyType type )
{
    setValue( "network/proxy/type", static_cast< uint >( type ) );
}


bool
HatchetSettings::proxyDns() const
{
    return value( "network/proxy/dns", false ).toBool();
}


void
HatchetSettings::setProxyDns( bool lookupViaProxy )
{
    setValue( "network/proxy/dns", lookupViaProxy );
}


QVariantList
HatchetSettings::aclEntries() const
{
    QVariant retVal = value( "acl/entries", QVariantList() );
    if ( retVal.isValid() && retVal.canConvert< QVariantList >() )
        return retVal.toList();

    return QVariantList();
}


void
HatchetSettings::setAclEntries( const QVariantList &entries )
{
    tDebug() << "Setting entries";
    setValue( "acl/entries", entries );
    sync();
    tDebug() << "Done setting entries";
}


bool
HatchetSettings::isSslCertKnown( const QByteArray& sslDigest ) const
{
    return value( "network/ssl/certs" ).toMap().contains( sslDigest );
}


bool
HatchetSettings::isSslCertTrusted( const QByteArray& sslDigest ) const
{
    return value( "network/ssl/certs" ).toMap().value( sslDigest, false ).toBool();
}


void
HatchetSettings::setSslCertTrusted( const QByteArray& sslDigest, bool trusted )
{
    QVariantMap map = value( "network/ssl/certs" ).toMap();
    map[ sslDigest ] = trusted;

    setValue( "network/ssl/certs", map );
}


QByteArray
HatchetSettings::mainWindowGeometry() const
{
    return value( "ui/mainwindow/geometry" ).toByteArray();
}


void
HatchetSettings::setMainWindowGeometry( const QByteArray& geom )
{
    setValue( "ui/mainwindow/geometry", geom );
}


QByteArray
HatchetSettings::mainWindowState() const
{
    return value( "ui/mainwindow/state" ).toByteArray();
}


void
HatchetSettings::setMainWindowState( const QByteArray& state )
{
    setValue( "ui/mainwindow/state", state );
}


QByteArray
HatchetSettings::mainWindowSplitterState() const
{
    return value( "ui/mainwindow/splitterState" ).toByteArray();
}


void
HatchetSettings::setMainWindowSplitterState( const QByteArray& state )
{
    setValue( "ui/mainwindow/splitterState", state );
}


bool
HatchetSettings::verboseNotifications() const
{
    return value( "ui/notifications/verbose", false ).toBool();
}


void
HatchetSettings::setVerboseNotifications( bool notifications )
{
    setValue( "ui/notifications/verbose", notifications );
}


bool
HatchetSettings::menuBarVisible() const
{
#ifndef Q_OS_MAC
    return value( "ui/mainwindow/menuBarVisible", true ).toBool();
#else
    return true;
#endif
}


void
HatchetSettings::setMenuBarVisible( bool visible )
{
#ifndef Q_OS_MAC
    setValue( "ui/mainwindow/menuBarVisible", visible );
#endif
}


bool
HatchetSettings::fullscreenEnabled() const
{
    return value( "ui/mainwindow/fullscreenEnabled", false ).toBool();
}


void
HatchetSettings::setFullscreenEnabled( bool enabled )
{
    setValue( "ui/mainwindow/fullscreenEnabled", enabled );
}


bool
HatchetSettings::showOfflineSources() const
{
    return value( "collection/sources/showoffline", false ).toBool();
}


void
HatchetSettings::setShowOfflineSources( bool show )
{
    setValue( "collection/sources/showoffline", show );
}


bool
HatchetSettings::enableEchonestCatalogs() const
{
    return value( "collection/enable_catalogs", false ).toBool();
}


void
HatchetSettings::setEnableEchonestCatalogs( bool enable )
{
    setValue( "collection/enable_catalogs", enable );
}


QByteArray
HatchetSettings::playlistColumnSizes( const QString& playlistid ) const
{
    return value( QString( "ui/playlist/%1/columnSizes" ).arg( playlistid ) ).toByteArray();
}


void
HatchetSettings::setPlaylistColumnSizes( const QString& playlistid, const QByteArray& state )
{
    if ( playlistid.isEmpty() )
        return;

    setValue( QString( "ui/playlist/%1/columnSizes" ).arg( playlistid ), state );
}


bool
HatchetSettings::shuffleState( const QString& playlistid ) const
{
    return value( QString( "ui/playlist/%1/shuffleState" ).arg( playlistid ) ).toBool();
}


void
HatchetSettings::setShuffleState( const QString& playlistid, bool state)
{
    setValue( QString( "ui/playlist/%1/shuffleState" ).arg( playlistid ), state );
}


void
HatchetSettings::removePlaylistSettings( const QString& playlistid )
{
    remove( QString( "ui/playlist/%1/shuffleState" ).arg( playlistid ) );
    remove( QString( "ui/playlist/%1/repeatMode" ).arg( playlistid ) );
}


QVariant
HatchetSettings::queueState() const
{
    return value( QString( "playlists/queue/state" ) );
}


void
HatchetSettings::setQueueState( const QVariant& state )
{
    setValue( QString( "playlists/queue/state" ), state );
}


void
HatchetSettings::setRepeatMode( const QString& playlistid, Hatchet::PlaylistModes::RepeatMode mode )
{
    setValue( QString( "ui/playlist/%1/repeatMode" ).arg( playlistid ), (int)mode );
}


Hatchet::PlaylistModes::RepeatMode
HatchetSettings::repeatMode( const QString& playlistid )
{
    return (PlaylistModes::RepeatMode)value( QString( "ui/playlist/%1/repeatMode" ).arg( playlistid ) ).toInt();
}


QStringList
HatchetSettings::recentlyPlayedPlaylistGuids( unsigned int amount ) const
{
    QStringList p = value( "playlists/recentlyPlayed" ).toStringList();

    while ( amount && p.count() > (int)amount )
        p.removeAt( 0 );

    return p;
}


void
HatchetSettings::appendRecentlyPlayedPlaylist( const QString& playlistguid, int sourceId )
{
    QStringList playlist_guids = value( "playlists/recentlyPlayed" ).toStringList();

    playlist_guids.removeAll( playlistguid );
    playlist_guids.append( playlistguid );

    setValue( "playlists/recentlyPlayed", playlist_guids );

    emit recentlyPlayedPlaylistAdded( playlistguid, sourceId );
}


QString
HatchetSettings::bookmarkPlaylist() const
{
    return value( "playlists/bookmark", QString() ).toString();
}


void
HatchetSettings::setBookmarkPlaylist( const QString& guid )
{
    setValue( "playlists/bookmark", guid );
}


QStringList
HatchetSettings::sipPlugins() const
{
    return value( "sip/allplugins", QStringList() ).toStringList();
}


void
HatchetSettings::setSipPlugins( const QStringList& plugins )
{
    setValue( "sip/allplugins", plugins );
}


QStringList
HatchetSettings::enabledSipPlugins() const
{
    return value( "sip/enabledplugins", QStringList() ).toStringList();
}


void
HatchetSettings::setEnabledSipPlugins( const QStringList& list )
{
    setValue( "sip/enabledplugins", list );
}


void
HatchetSettings::enableSipPlugin( const QString& pluginId )
{
    QStringList list = enabledSipPlugins();
    list << pluginId;
    setEnabledSipPlugins( list );
}


void
HatchetSettings::disableSipPlugin( const QString& pluginId )
{
    QStringList list = enabledSipPlugins();
    list.removeAll( pluginId );
    setEnabledSipPlugins( list );
}


void
HatchetSettings::addSipPlugin( const QString& pluginId, bool enable )
{
    QStringList list = sipPlugins();
    list << pluginId;
    setSipPlugins( list );

    if ( enable )
        enableSipPlugin( pluginId );
}


void
HatchetSettings::removeSipPlugin( const QString& pluginId )
{
    QStringList list = sipPlugins();
    list.removeAll( pluginId );
    setSipPlugins( list );

    if( enabledSipPlugins().contains( pluginId ) )
        disableSipPlugin( pluginId );
}


QStringList
HatchetSettings::accounts() const
{
    QStringList accounts = value( "accounts/allaccounts", QStringList() ).toStringList();
    accounts.removeDuplicates();

    return accounts;
}


void
HatchetSettings::setAccounts( const QStringList& accountIds )
{
    QStringList accounts = accountIds;
    accounts.removeDuplicates();

    setValue( "accounts/allaccounts", accounts );
}


void
HatchetSettings::addAccount( const QString& accountId )
{
    QStringList list = accounts();
    list << accountId;
    setAccounts( list );
}


void
HatchetSettings::removeAccount( const QString& accountId )
{
    QStringList list = accounts();
    list.removeAll( accountId );
    setAccounts( list );
}


Hatchet::Network::ExternalAddress::Mode
HatchetSettings::externalAddressMode()
{
    if ( value( "network/prefer-static-host-and-port", false ).toBool() )
    {
        remove( "network/prefer-static-host-and-port" );
        setValue( "network/external-address-mode", Hatchet::Network::ExternalAddress::Static );
    }
    return (Hatchet::Network::ExternalAddress::Mode) value( "network/external-address-mode", Hatchet::Network::ExternalAddress::Upnp ).toInt();
}


void
HatchetSettings::setExternalAddressMode( Hatchet::Network::ExternalAddress::Mode externalAddressMode )
{
    setValue( "network/external-address-mode", externalAddressMode );
}


QString
HatchetSettings::externalHostname() const
{
    return value( "network/external-hostname" ).toString();
}


void
HatchetSettings::setExternalHostname(const QString& externalHostname)
{
    setValue( "network/external-hostname", externalHostname );
}


int
HatchetSettings::defaultPort() const
{
    return 50210;
}


int
HatchetSettings::externalPort() const
{
    return value( "network/external-port", 50210 ).toInt();
}


void
HatchetSettings::setExternalPort(int externalPort)
{
    if ( externalPort == 0 )
        setValue( "network/external-port", 50210);
    else
        setValue( "network/external-port", externalPort);
}


QString
HatchetSettings::xmppBotServer() const
{
    return value( "xmppBot/server", QString() ).toString();
}


void
HatchetSettings::setXmppBotServer( const QString& server )
{
    setValue( "xmppBot/server", server );
}


QString
HatchetSettings::xmppBotJid() const
{
    return value( "xmppBot/jid", QString() ).toString();
}


void
HatchetSettings::setXmppBotJid( const QString& component )
{
    setValue( "xmppBot/jid", component );
}


QString
HatchetSettings::xmppBotPassword() const
{
    return value( "xmppBot/password", QString() ).toString();
}


void
HatchetSettings::setXmppBotPassword( const QString& password )
{
    setValue( "xmppBot/password", password );
}


int
HatchetSettings::xmppBotPort() const
{
    return value( "xmppBot/port", -1 ).toInt();
}


void
HatchetSettings::setXmppBotPort( const int port )
{
    setValue( "xmppBot/port", port );
}


QString
HatchetSettings::scriptDefaultPath() const
{
    return value( "script/defaultpath", QDir::homePath() ).toString();
}


void
HatchetSettings::setScriptDefaultPath( const QString& path )
{
    setValue( "script/defaultpath", path );
}


QString
HatchetSettings::playlistDefaultPath() const
{
    return value( "playlists/defaultpath", QDir::homePath() ).toString();
}


void
HatchetSettings::setPlaylistDefaultPath( const QString& path )
{
    setValue( "playlists/defaultpath", path );
}


bool
HatchetSettings::nowPlayingEnabled() const
{
    return value( "adium/enablenowplaying", false ).toBool();
}


void
HatchetSettings::setNowPlayingEnabled( bool enable )
{
    setValue( "adium/enablenowplaying", enable );
}


HatchetSettings::PrivateListeningMode
HatchetSettings::privateListeningMode() const
{
    return ( HatchetSettings::PrivateListeningMode ) value( "privatelisteningmode", HatchetSettings::PublicListening ).toInt();
}


void
HatchetSettings::setPrivateListeningMode( HatchetSettings::PrivateListeningMode mode )
{
    setValue( "privatelisteningmode", mode );
}


void
HatchetSettings::updateIndex()
{
    if ( !Database::instance() || !Database::instance()->isReady() )
    {
        QTimer::singleShot( 0, this, SLOT( updateIndex() ) );
        return;
    }

    tDebug() << Q_FUNC_INFO << "Updating fuzzy index.";

    Hatchet::DatabaseCommand* cmd = new Hatchet::DatabaseCommand_UpdateSearchIndex();
    Database::instance()->enqueue( QSharedPointer<Hatchet::DatabaseCommand>( cmd ) );
}


QString
HatchetSettings::importPlaylistPath() const
{
    if ( contains( "importPlaylistPath" ) )
        return value( "importPlaylistPath" ).toString();
    else
        return QDir::homePath();
}


void
HatchetSettings::setImportPlaylistPath( const QString& path )
{
    setValue( "importPlaylistPath", path );
}


SerializedUpdaters
HatchetSettings::playlistUpdaters() const
{
    return value( "playlists/updaters" ).value< SerializedUpdaters >();
}


void
HatchetSettings::setPlaylistUpdaters( const SerializedUpdaters& updaters )
{
    setValue( "playlists/updaters", QVariant::fromValue< SerializedUpdaters >( updaters ) );
}


void
HatchetSettings::setLastChartIds( const QMap<QString, QVariant>& ids ){

    setValue( "chartIds", QVariant::fromValue<QMap<QString, QVariant> >( ids ) );
}


QMap<QString, QVariant> HatchetSettings::lastChartIds(){

    return value( "chartIds" ).value<QMap<QString, QVariant> >();
}


inline QDataStream&
operator<<( QDataStream& out, const AtticaManager::StateHash& states )
{
    out <<  HATCHET_SETTINGS_VERSION;
    out << (quint32)states.count();
    foreach( const QString& key, states.keys() )
    {
        AtticaManager::Resolver resolver = states[ key ];
        out << key << resolver.version << resolver.scriptPath << (qint32)resolver.state << resolver.userRating << resolver.binary;
    }
    return out;
}


inline QDataStream&
operator>>( QDataStream& in, AtticaManager::StateHash& states )
{
    quint32 count = 0, configVersion = 0;
    in >> configVersion;
    in >> count;
    for ( uint i = 0; i < count; i++ )
    {
        QString key, version, scriptPath;
        qint32 state, userRating;
        bool binary = false;
        in >> key;
        in >> version;
        in >> scriptPath;
        in >> state;
        in >> userRating;
        if ( configVersion > 10 )
        {
            // V11 includes 'bool binary' flag
            in >> binary;
        }
        states[ key ] = AtticaManager::Resolver( version, scriptPath, userRating, (AtticaManager::ResolverState)state, binary );
    }
    return in;
}


void
HatchetSettings::registerCustomSettingsHandlers()
{
    qRegisterMetaType< Hatchet::SerializedUpdater >( "Hatchet::SerializedUpdater" );
    qRegisterMetaType< Hatchet::SerializedUpdaters >( "Hatchet::SerializedUpdaters" );
    qRegisterMetaTypeStreamOperators< Hatchet::SerializedUpdaters >( "Hatchet::SerializedUpdaters" );

    qRegisterMetaType< AtticaManager::StateHash >( "AtticaManager::StateHash" );
    qRegisterMetaTypeStreamOperators< AtticaManager::StateHash >( "AtticaManager::StateHash" );
}


void
HatchetSettings::setAtticaResolverState( const QString& resolver, AtticaManager::ResolverState state )
{
    AtticaManager::StateHash resolvers = value( "script/atticaresolverstates" ).value< AtticaManager::StateHash >();
    AtticaManager::Resolver r = resolvers.value( resolver );
    r.state = state;
    resolvers.insert( resolver, r );
    setValue( "script/atticaresolverstates", QVariant::fromValue< AtticaManager::StateHash >( resolvers ) );

    sync();
}


AtticaManager::StateHash
HatchetSettings::atticaResolverStates() const
{
    return value( "script/atticaresolverstates" ).value< AtticaManager::StateHash >();
}


void
HatchetSettings::setAtticaResolverStates( const AtticaManager::StateHash states )
{
    setValue( "script/atticaresolverstates", QVariant::fromValue< AtticaManager::StateHash >( states ) );
}


void
HatchetSettings::removeAtticaResolverState ( const QString& resolver )
{
    AtticaManager::StateHash resolvers = value( "script/atticaresolverstates" ).value< AtticaManager::StateHash >();
    resolvers.remove( resolver );
    setValue( "script/atticaresolverstates", QVariant::fromValue< AtticaManager::StateHash >( resolvers ) );
}


QByteArray
HatchetSettings::playdarCertificate() const
{
    return value( "playdar/certificate").value< QByteArray >();
}


void
HatchetSettings::setPlaydarCertificate( const QByteArray& cert )
{
    setValue( "playdar/certificate", cert );
}


QByteArray
HatchetSettings::playdarKey() const
{
    return value( "playdar/key" ).value< QByteArray >();
}


void
HatchetSettings::setPlaydarKey( const QByteArray& key )
{
    setValue( "playdar/key", key );
}

QString
HatchetSettings::vlcArguments() const
{
    return value( "vlc/cmdline_args" ).value< QString >();
}

void
HatchetSettings::setVlcArguments( const QString& args )
{
    setValue( "vlc/cmdline_args", args);
}

