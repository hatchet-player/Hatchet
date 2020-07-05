# libhatchet filemetadata file
#============================================================================



libhatchet_inc += include_directories('.', 'taghandlers')
libhatchet_filemetadata_dir = meson.current_source_dir()


libhatchet_src += files(
    join_paths(libhatchet_filemetadata_dir, 'MusicScanner.cpp'),
    join_paths(libhatchet_filemetadata_dir,'ScanManager.cpp'),
    join_paths(libhatchet_filemetadata_dir,'taghandlers/tag.cpp'),
    join_paths(libhatchet_filemetadata_dir,'taghandlers/apetag.cpp'),
    join_paths(libhatchet_filemetadata_dir,'taghandlers/asftag.cpp'),
    join_paths(libhatchet_filemetadata_dir,'taghandlers/id3v1tag.cpp'),
    join_paths(libhatchet_filemetadata_dir,'taghandlers/id3v2tag.cpp'),
    join_paths(libhatchet_filemetadata_dir,'taghandlers/mp4tag.cpp'),
    join_paths(libhatchet_filemetadata_dir,'taghandlers/oggtag.cpp'),
    join_paths(libhatchet_filemetadata_dir,'MetadataEditor.cpp'))

libhatchet_moc_h += files(
    join_paths(libhatchet_filemetadata_dir, 'MetadataEditor.h'),
    join_paths(libhatchet_filemetadata_dir, 'MusicScanner.h'),
    join_paths(libhatchet_filemetadata_dir, 'ScanManager.h'))


libhatchet_moc_ui += files(
    join_paths(libhatchet_filemetadata_dir, 'MetadataEditor.ui'))
    