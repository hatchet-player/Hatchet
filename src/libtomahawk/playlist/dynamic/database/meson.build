# libtomahawk.playlist.dynamic.database build file
#============================================================================


libtomahawk_inc += include_directories('.')
libtomahawk_playlist_dynamic_database_dir = meson.current_source_dir()


libtomahawk_src += files(
    join_paths(libtomahawk_playlist_dynamic_database_dir, 'DatabaseControl.cpp'),
    join_paths(libtomahawk_playlist_dynamic_database_dir, 'DatabaseGenerator.cpp'))

libtomahawk_moc_h += files(
    join_paths(libtomahawk_playlist_dynamic_database_dir, 'DatabaseControl.h'),
    join_paths(libtomahawk_playlist_dynamic_database_dir, 'DatabaseGenerator.h'))