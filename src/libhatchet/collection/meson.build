# libhatchet collection build file
#============================================================================

libhatchet_inc += include_directories('.')
libhatchet_collection_dir = meson.current_source_dir()


libhatchet_src += files(
    join_paths(libhatchet_collection_dir, 'AlbumsRequest.cpp'),
    join_paths(libhatchet_collection_dir, 'ArtistsRequest.cpp'),
    join_paths(libhatchet_collection_dir, 'Collection.cpp'),
    join_paths(libhatchet_collection_dir, 'TracksRequest.cpp'))


libhatchet_h += files()

libhatchet_moc_src += files ()

libhatchet_moc_h += files(
    join_paths(libhatchet_collection_dir, 'Collection.h'))
