# libtomahwak.viewpages build file
#============================================================================

libhatchet_inc += include_directories('.')
libhatchet_viewpages_dir = meson.current_source_dir()


libhatchet_gui_src += files(
    join_paths(libhatchet_viewpages_dir, 'SearchViewPage.cpp'),
    join_paths(libhatchet_viewpages_dir, 'SourceViewPage.cpp'),
    join_paths(libhatchet_viewpages_dir, 'ArtistViewPage.cpp'),
    join_paths(libhatchet_viewpages_dir, 'AlbumViewPage.cpp'),
    join_paths(libhatchet_viewpages_dir, 'TrackViewPage.cpp'),
    join_paths(libhatchet_viewpages_dir, 'PlaylistViewPage.cpp'),
    join_paths(libhatchet_viewpages_dir, 'CollectionViewPage.cpp'))


libhatchet_moc_ui += files(
    join_paths(libhatchet_viewpages_dir, 'SearchViewPage.ui'),
    join_paths(libhatchet_viewpages_dir, 'SourceViewPage.ui'),
    join_paths(libhatchet_viewpages_dir, 'ArtistViewPage.ui'),
    join_paths(libhatchet_viewpages_dir, 'AlbumViewPage.ui'),
    join_paths(libhatchet_viewpages_dir, 'TrackViewPage.ui'))

libhatchet_moc_h += files (
    join_paths(libhatchet_viewpages_dir, 'AlbumViewPage.h'),
    join_paths(libhatchet_viewpages_dir, 'ArtistViewPage.h'),
    join_paths(libhatchet_viewpages_dir, 'CollectionViewPage.h'),
    join_paths(libhatchet_viewpages_dir, 'PlaylistViewPage.h'),
    join_paths(libhatchet_viewpages_dir, 'SearchViewPage.h'),
    join_paths(libhatchet_viewpages_dir, 'SourceViewPage.h'),
    join_paths(libhatchet_viewpages_dir, 'TrackViewPage.h'))