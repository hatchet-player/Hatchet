# libtomahawk infosystem build file
#============================================================================


libtomahawk_inc += include_directories('.')
libtomahawk_infosystem_dir = meson.current_source_dir()


libtomahawk_src += files(
    join_paths(libtomahawk_infosystem_dir, 'InfoSystem.cpp'),
    join_paths(libtomahawk_infosystem_dir, 'InfoSystemCache.cpp'),
    join_paths(libtomahawk_infosystem_dir, 'InfoSystemWorker.cpp'))


libtomahawk_moc_h += files(
    join_paths(libtomahawk_infosystem_dir, 'InfoSystem.h'),
    join_paths(libtomahawk_infosystem_dir, 'InfoSystemCache.h'),
    join_paths(libtomahawk_infosystem_dir, 'InfoSystemWorker.h'))