# libtomahwak.viewpages build file
#============================================================================

libtomahawk_inc += include_directories('.')
libtomahawk_viewpages_dir = meson.current_source_dir()


libtomahawk_gui_src += files(
    join_paths(libtomahawk_viewpages_dir, 'SearchViewPage.cpp'),
    join_paths(libtomahawk_viewpages_dir, 'SourceViewPage.cpp'),
    join_paths(libtomahawk_viewpages_dir, 'ArtistViewPage.cpp'),
    join_paths(libtomahawk_viewpages_dir, 'AlbumViewPage.cpp'),
    join_paths(libtomahawk_viewpages_dir, 'TrackViewPage.cpp'),
    join_paths(libtomahawk_viewpages_dir, 'PlaylistViewPage.cpp'),
    join_paths(libtomahawk_viewpages_dir, 'CollectionViewPage.cpp'))


libtomahawk_moc_ui += files(
    join_paths(libtomahawk_viewpages_dir, 'SearchViewPage.ui'),
    join_paths(libtomahawk_viewpages_dir, 'SourceViewPage.ui'),
    join_paths(libtomahawk_viewpages_dir, 'ArtistViewPage.ui'),
    join_paths(libtomahawk_viewpages_dir, 'AlbumViewPage.ui'),
    join_paths(libtomahawk_viewpages_dir, 'TrackViewPage.ui'))

libtomahawk_moc_h += files (
    join_paths(libtomahawk_viewpages_dir, 'AlbumViewPage.h'),
    join_paths(libtomahawk_viewpages_dir, 'ArtistViewPage.h'),
    join_paths(libtomahawk_viewpages_dir, 'CollectionViewPage.h'),
    join_paths(libtomahawk_viewpages_dir, 'PlaylistViewPage.h'),
    join_paths(libtomahawk_viewpages_dir, 'SearchViewPage.h'),
    join_paths(libtomahawk_viewpages_dir, 'SourceViewPage.h'),
    join_paths(libtomahawk_viewpages_dir, 'TrackViewPage.h'))