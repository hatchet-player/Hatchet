# libtomahawk collection build file
#============================================================================

libtomahawk_inc += include_directories('.')
libtomahawk_collection_dir = meson.current_source_dir()


libtomahawk_src += files(
    join_paths(libtomahawk_collection_dir, 'AlbumsRequest.cpp'),
    join_paths(libtomahawk_collection_dir, 'ArtistsRequest.cpp'),
    join_paths(libtomahawk_collection_dir, 'Collection.cpp'),
    join_paths(libtomahawk_collection_dir, 'TracksRequest.cpp'))


libtomahawk_h += files()

libtomahawk_moc_src += files ()

libtomahawk_moc_h += files(
    join_paths(libtomahawk_collection_dir, 'Collection.h'))
