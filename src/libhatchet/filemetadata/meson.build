# libtomahawk filemetadata file
#============================================================================



libtomahawk_inc += include_directories('.', 'taghandlers')
libtomahawk_filemetadata_dir = meson.current_source_dir()


libtomahawk_src += files(
    join_paths(libtomahawk_filemetadata_dir, 'MusicScanner.cpp'),
    join_paths(libtomahawk_filemetadata_dir,'ScanManager.cpp'),
    join_paths(libtomahawk_filemetadata_dir,'taghandlers/tag.cpp'),
    join_paths(libtomahawk_filemetadata_dir,'taghandlers/apetag.cpp'),
    join_paths(libtomahawk_filemetadata_dir,'taghandlers/asftag.cpp'),
    join_paths(libtomahawk_filemetadata_dir,'taghandlers/id3v1tag.cpp'),
    join_paths(libtomahawk_filemetadata_dir,'taghandlers/id3v2tag.cpp'),
    join_paths(libtomahawk_filemetadata_dir,'taghandlers/mp4tag.cpp'),
    join_paths(libtomahawk_filemetadata_dir,'taghandlers/oggtag.cpp'),
    join_paths(libtomahawk_filemetadata_dir,'MetadataEditor.cpp'))

libtomahawk_moc_h += files(
    join_paths(libtomahawk_filemetadata_dir, 'MetadataEditor.h'),
    join_paths(libtomahawk_filemetadata_dir, 'MusicScanner.h'),
    join_paths(libtomahawk_filemetadata_dir, 'ScanManager.h'))


libtomahawk_moc_ui += files(
    join_paths(libtomahawk_filemetadata_dir, 'MetadataEditor.ui'))
    