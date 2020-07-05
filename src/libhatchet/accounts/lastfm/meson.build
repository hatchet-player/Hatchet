# libhatchet.accounts.lastfm build file
#============================================================================

libhatchet_inc += include_directories('.')
libhatchet_lastfm_dir = meson.current_source_dir()



libhatchet_src += files(
    join_paths(libhatchet_lastfm_dir, 'LastFmAccount.cpp'),
    join_paths(libhatchet_lastfm_dir, 'LastFmConfig.cpp'),
    join_paths(libhatchet_lastfm_dir, 'LastFmInfoPlugin.cpp'))

libhatchet_moc_h += files(
    join_paths(libhatchet_lastfm_dir, 'LastFmAccount.h'),
    join_paths(libhatchet_lastfm_dir, 'LastFmConfig.h'),
    join_paths(libhatchet_lastfm_dir, 'LastFmInfoPlugin.h'))

libhatchet_moc_ui += files(
    join_paths(libhatchet_lastfm_dir, 'LastFmConfig.ui'))


