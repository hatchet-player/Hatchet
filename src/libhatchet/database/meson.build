# libhatchet database build file
#============================================================================

libhatchet_inc += include_directories('.')
libhatchet_database_dir = meson.current_source_dir()


libhatchet_src += files(
    join_paths(libhatchet_database_dir, 'Database.cpp'),
    join_paths(libhatchet_database_dir, 'DatabaseCollection.cpp'),
    join_paths(libhatchet_database_dir, 'DatabaseCommand.cpp'),
    join_paths(libhatchet_database_dir, 'DatabaseCommandLoggable.cpp'),
    join_paths(libhatchet_database_dir, 'DatabaseImpl.cpp'),
    join_paths(libhatchet_database_dir, 'DatabaseResolver.cpp'),
    join_paths(libhatchet_database_dir, 'DatabaseWorker.cpp'),
    join_paths(libhatchet_database_dir, 'IdThreadWorker.cpp'),
    join_paths(libhatchet_database_dir, 'LocalCollection.cpp'),
    join_paths(libhatchet_database_dir, 'HatchetSqlQuery.cpp'))

libhatchet_moc_src += files()


libhatchet_moc_h += files(
    join_paths(libhatchet_database_dir, 'Database.h'),
    join_paths(libhatchet_database_dir, 'DatabaseCollection.h'),
    join_paths(libhatchet_database_dir, 'DatabaseCommand.h'),
    join_paths(libhatchet_database_dir, 'DatabaseCommandLoggable.h'),
    join_paths(libhatchet_database_dir, 'DatabaseImpl.h'),
    join_paths(libhatchet_database_dir, 'DatabaseResolver.h'),
    join_paths(libhatchet_database_dir, 'DatabaseWorker.h'),
    join_paths(libhatchet_database_dir, 'IdThreadWorker.h'),
    join_paths(libhatchet_database_dir, 'LocalCollection.h'))


database_dirs = [
    'fuzzyindex',
    'commands']


foreach dir : database_dirs
    subdir(dir)
endforeach