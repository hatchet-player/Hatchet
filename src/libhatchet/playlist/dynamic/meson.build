# libhatchet.playlist.dynamic build file
#============================================================================


libhatchet_inc += include_directories('.')
libhatchet_playlist_dynamic_dir = meson.current_source_dir()


libhatchet_src += files(
    join_paths(libhatchet_playlist_dynamic_dir, 'DynamicPlaylist.cpp'),
    join_paths(libhatchet_playlist_dynamic_dir, 'GeneratorFactory.cpp'),
    join_paths(libhatchet_playlist_dynamic_dir, 'GeneratorInterface.cpp'),
    join_paths(libhatchet_playlist_dynamic_dir, 'DynamicPlaylistRevision.cpp'),
    join_paths(libhatchet_playlist_dynamic_dir, 'DynamicControl.cpp'))


libhatchet_gui_src += files(
    join_paths(libhatchet_playlist_dynamic_dir, 'DynamicPlaylist.cpp'),
    join_paths(libhatchet_playlist_dynamic_dir, 'DynamicView.cpp'),
    join_paths(libhatchet_playlist_dynamic_dir, 'DynamicModel.cpp'))


libhatchet_moc_h += files(
    join_paths(libhatchet_playlist_dynamic_dir, 'DynamicControl.h'),
    join_paths(libhatchet_playlist_dynamic_dir, 'DynamicModel.h'),
    join_paths(libhatchet_playlist_dynamic_dir, 'DynamicPlaylist.h'),
    join_paths(libhatchet_playlist_dynamic_dir, 'DynamicView.h'),
    join_paths(libhatchet_playlist_dynamic_dir, 'GeneratorInterface.h'))

libhatchet_playlist_dynamic_dirs = [
    'database',
    'widgets']


foreach dir : libhatchet_playlist_dynamic_dirs
    subdir(dir)
endforeach
    