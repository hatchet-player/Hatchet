# libtomahawk.accounts.lastfm build file
#============================================================================

libtomahawk_inc += include_directories('.')
libtomahawk_lastfm_dir = meson.current_source_dir()



libtomahawk_src += files(
    join_paths(libtomahawk_lastfm_dir, 'LastFmAccount.cpp'),
    join_paths(libtomahawk_lastfm_dir, 'LastFmConfig.cpp'),
    join_paths(libtomahawk_lastfm_dir, 'LastFmInfoPlugin.cpp'))

libtomahawk_moc_h += files(
    join_paths(libtomahawk_lastfm_dir, 'LastFmAccount.h'),
    join_paths(libtomahawk_lastfm_dir, 'LastFmConfig.h'),
    join_paths(libtomahawk_lastfm_dir, 'LastFmInfoPlugin.h'))

libtomahawk_moc_ui += files(
    join_paths(libtomahawk_lastfm_dir, 'LastFmConfig.ui'))


