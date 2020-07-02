# libtomahawk.accounts.spotify build file
#============================================================================

libtomahawk_inc += include_directories('.')
libtomahawk_accounts_spotify_dir = meson.current_source_dir()


libtomahawk_src += files(
    join_paths(libtomahawk_accounts_spotify_dir, 'SpotifyAccount.cpp'),
    join_paths(libtomahawk_accounts_spotify_dir, 'SpotifyAccountConfig.cpp'),
    # join_paths(libtomahawk_accounts_spotify_dir, 'SpotifyPlaylistUpdater.cpp'),
    join_paths(libtomahawk_accounts_spotify_dir, 'SpotifyInfoPlugin.cpp'))


libtomahawk_moc_h += files(
    join_paths(libtomahawk_accounts_spotify_dir, 'SpotifyAccount.h'),
    join_paths(libtomahawk_accounts_spotify_dir, 'SpotifyAccountConfig.h'),
    # join_paths(libtomahawk_accounts_spotify_dir, 'SpotifyPlaylistUpdater.h'),
    join_paths(libtomahawk_accounts_spotify_dir, 'SpotifyInfoPlugin.h'))


libtomahawk_moc_ui += files(
    join_paths(libtomahawk_accounts_spotify_dir, 'SpotifyAccountConfig.ui'))