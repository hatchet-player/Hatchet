# libhatchet.accounts.spotify build file
#============================================================================

libhatchet_inc += include_directories('.')
libhatchet_accounts_spotify_dir = meson.current_source_dir()


libhatchet_src += files(
    join_paths(libhatchet_accounts_spotify_dir, 'SpotifyAccount.cpp'),
    join_paths(libhatchet_accounts_spotify_dir, 'SpotifyAccountConfig.cpp'),
    # join_paths(libhatchet_accounts_spotify_dir, 'SpotifyPlaylistUpdater.cpp'),
    join_paths(libhatchet_accounts_spotify_dir, 'SpotifyInfoPlugin.cpp'))


libhatchet_moc_h += files(
    join_paths(libhatchet_accounts_spotify_dir, 'SpotifyAccount.h'),
    join_paths(libhatchet_accounts_spotify_dir, 'SpotifyAccountConfig.h'),
    # join_paths(libhatchet_accounts_spotify_dir, 'SpotifyPlaylistUpdater.h'),
    join_paths(libhatchet_accounts_spotify_dir, 'SpotifyInfoPlugin.h'))


libhatchet_moc_ui += files(
    join_paths(libhatchet_accounts_spotify_dir, 'SpotifyAccountConfig.ui'))