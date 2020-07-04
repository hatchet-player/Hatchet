# libtomahawk.playlist.dynamic build file
#============================================================================


libtomahawk_inc += include_directories('.')
libtomahawk_playlist_dynamic_dir = meson.current_source_dir()


libtomahawk_src += files(
    join_paths(libtomahawk_playlist_dynamic_dir, 'DynamicPlaylist.cpp'),
    join_paths(libtomahawk_playlist_dynamic_dir, 'GeneratorFactory.cpp'),
    join_paths(libtomahawk_playlist_dynamic_dir, 'GeneratorInterface.cpp'),
    join_paths(libtomahawk_playlist_dynamic_dir, 'DynamicPlaylistRevision.cpp'),
    join_paths(libtomahawk_playlist_dynamic_dir, 'DynamicControl.cpp'))


libtomahawk_gui_src += files(
    join_paths(libtomahawk_playlist_dynamic_dir, 'DynamicPlaylist.cpp'),
    join_paths(libtomahawk_playlist_dynamic_dir, 'DynamicView.cpp'),
    join_paths(libtomahawk_playlist_dynamic_dir, 'DynamicModel.cpp'))


libtomahawk_moc_h += files(
    join_paths(libtomahawk_playlist_dynamic_dir, 'DynamicControl.h'),
    join_paths(libtomahawk_playlist_dynamic_dir, 'DynamicModel.h'),
    join_paths(libtomahawk_playlist_dynamic_dir, 'DynamicPlaylist.h'),
    join_paths(libtomahawk_playlist_dynamic_dir, 'DynamicView.h'),
    join_paths(libtomahawk_playlist_dynamic_dir, 'GeneratorInterface.h'))

libtomahawk_playlist_dynamic_dirs = [
    'database',
    'echonest',
    'widgets']


foreach dir : libtomahawk_playlist_dynamic_dirs
    subdir(dir)
endforeach
    