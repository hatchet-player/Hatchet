# libtomahawk build file
#============================================================================


libtomahawk_dir = meson.current_source_dir()
libtomahawk_inc = [include_directories('.')]
libtomahawk_inc += tomahawk_inc


# dependancies
#============================================================================

libtomahawk_dep_list = [
    zlib_dep,
    boost_dep,
    qca2_dep,
    qt5_dep,
    qtkeychain_dep,
    quazip_dep,
    kf5attica_dep,
    liblucene_dep,
    libvlc_dep,
    libportfwd_dep,
    telepathy_dep,
    echonest_dep]



if (get_option('with_taglib'))
    libtomahawk_dep_list += taglib_dep
endif

if (get_option('with_liblastfm'))
    libtomahawk_dep_list += liblastfm_dep
endif

# src
#============================================================================


libtomahawk_src = files(
    join_paths(libtomahawk_dir, 'EchonestCatalogSynchronizer.cpp'),
    join_paths(libtomahawk_dir, 'TomahawkSettings.cpp'),
    join_paths(libtomahawk_dir, 'SourceList.cpp'),
    join_paths(libtomahawk_dir, 'Pipeline.cpp'),
    join_paths(libtomahawk_dir, 'Artist.cpp'),
    join_paths(libtomahawk_dir, 'ArtistPlaylistInterface.cpp'),
    join_paths(libtomahawk_dir, 'Album.cpp'),
    join_paths(libtomahawk_dir, 'AlbumPlaylistInterface.cpp'),
    join_paths(libtomahawk_dir, 'CountryUtils.cpp'),
    join_paths(libtomahawk_dir, 'FuncTimeout.cpp'),
    join_paths(libtomahawk_dir, 'Playlist.cpp'),
    join_paths(libtomahawk_dir, 'PlaylistEntry.cpp'),
    join_paths(libtomahawk_dir, 'PlaylistPlaylistInterface.cpp'),
    join_paths(libtomahawk_dir, 'MetaPlaylistInterface.cpp'),
    join_paths(libtomahawk_dir, 'Query.cpp'),
    join_paths(libtomahawk_dir, 'Result.cpp'),
    join_paths(libtomahawk_dir, 'Source.cpp'),
    join_paths(libtomahawk_dir, 'Track.cpp'),
    join_paths(libtomahawk_dir, 'TrackData.cpp'),
    join_paths(libtomahawk_dir, 'SourcePlaylistInterface.cpp'),
    join_paths(libtomahawk_dir, 'PlaylistInterface.cpp'),
    join_paths(libtomahawk_dir, 'UrlHandler.cpp'))


libtomahawk_gui_src = files(
    join_paths(libtomahawk_dir, 'ActionCollection.cpp'),
    join_paths(libtomahawk_dir, 'ContextMenu.cpp'),
    join_paths(libtomahawk_dir, 'DownloadManager.cpp'),
    join_paths(libtomahawk_dir, 'DownloadJob.cpp'),
    join_paths(libtomahawk_dir, 'DropJob.cpp'),
    join_paths(libtomahawk_dir, 'GlobalActionManager.cpp'),
    join_paths(libtomahawk_dir, 'ViewPage.cpp'),
    join_paths(libtomahawk_dir, 'ViewPageLazyLoader.cpp'),
    join_paths(libtomahawk_dir, 'ViewPagePlugin.cpp'),
    join_paths(libtomahawk_dir, 'ViewManager.cpp'),
    join_paths(libtomahawk_dir, 'LatchManager.cpp'))


libtomahawk_h = files()


libtomahawk_moc_ui = files()


libtomahawk_moc_src = files()


libtomahawk_moc_h = files(
    join_paths(libtomahawk_dir, 'ActionCollection.h'),
    join_paths(libtomahawk_dir, 'Album.h'),
    join_paths(libtomahawk_dir, 'AlbumPlaylistInterface.h'),
    join_paths(libtomahawk_dir, 'Artist.h'),
    join_paths(libtomahawk_dir, 'ArtistPlaylistInterface.h'),
    join_paths(libtomahawk_dir, 'AtticaManager.h'),
    join_paths(libtomahawk_dir, 'ContextMenu.h'),
    join_paths(libtomahawk_dir, 'DownloadJob.h'),
    join_paths(libtomahawk_dir, 'DownloadManager.h'),
    join_paths(libtomahawk_dir, 'DropJob.h'),
    join_paths(libtomahawk_dir, 'EchonestCatalogSynchronizer.h'),
    join_paths(libtomahawk_dir, 'FuncTimeout.h'),
    join_paths(libtomahawk_dir, 'GlobalActionManager.h'),
    join_paths(libtomahawk_dir, 'LatchManager.h'),
    join_paths(libtomahawk_dir, 'MetaPlaylistInterface.h'),
    join_paths(libtomahawk_dir, 'Pipeline.h'),
    join_paths(libtomahawk_dir, 'PlaylistEntry.h'),
    join_paths(libtomahawk_dir, 'Playlist.h'),
    join_paths(libtomahawk_dir, 'PlaylistInterface.h'),
    join_paths(libtomahawk_dir, 'PlaylistPlaylistInterface.h'),
    join_paths(libtomahawk_dir, 'Query.h'),
    join_paths(libtomahawk_dir, 'Result.h'),
    join_paths(libtomahawk_dir, 'Source.h'),
    join_paths(libtomahawk_dir, 'SourceList.h'),
    join_paths(libtomahawk_dir, 'SourcePlaylistInterface.h'),
    join_paths(libtomahawk_dir, 'TomahawkSettings.h'),
    join_paths(libtomahawk_dir, 'TrackData.h'),
    join_paths(libtomahawk_dir, 'Track.h'),
    join_paths(libtomahawk_dir, 'UrlHandler_p.h'),
    join_paths(libtomahawk_dir, 'ViewManager.h'),
    join_paths(libtomahawk_dir, 'ViewPagePlugin.h'))


libtomahawk_dirs = [
  'accounts',
  'audio',
  'collection',
  'database',
  'filemetadata',
  'infosystem',
  'jobview',
  'mac',
  'network',
  'playlist',
  'resolvers',
  'sip',
  'thirdparty',
  'utils',
  'viewpages',
  'widgets']


foreach dir : libtomahawk_dirs
    subdir(dir)
endforeach


if (kf5attica_dep.found())
    libtomahawk_gui_src += files(
        join_paths(libtomahawk_dir, 'AtticaManager.cpp'))
endif



# Build args
#============================================================================


libtomahawk_link_list = [
    libtomahawk_telepathy_lib]


libtomahawk_link_args = []


if (get_option('with_gui'))
    libtomahawk_src += libtomahawk_gui_src
endif


# build
#============================================================================


libtomahawk_qt_src = qt5.preprocess(
    moc_sources : libtomahawk_moc_src,
    include_directories : libtomahawk_inc,
    dependencies : libtomahawk_dep_list)

libtomahawk_qt_ui = qt5.preprocess(
    ui_files : libtomahawk_moc_ui,
    include_directories : libtomahawk_inc,
    dependencies : libtomahawk_dep_list)

libtomahawk_qt_h = qt5.preprocess(
    moc_headers : libtomahawk_moc_h,
    include_directories : libtomahawk_inc,
    dependencies : libtomahawk_dep_list)


libtomahawk_lib = shared_library(
    'tomahawk',
    sources : [
        libtomahawk_src,
        libtomahawk_qt_src,
        libtomahawk_qt_ui,
        libtomahawk_qt_h],
    install : true,
    install_mode : 'rwxr-xr-x',
    install_dir : libdir,
    include_directories : libtomahawk_inc,
    link_with : libtomahawk_link_list,
    link_args : libtomahawk_link_args,
    dependencies : libtomahawk_dep_list)


install_headers(
    libtomahawk_h,
    install_dir : join_paths(includedir, ''))


libtomahawk_config = pkg.generate(
    libtomahawk_lib,
    libraries : [],
    version : meson.project_version(),
    name : 'Tomahawk',
    subdirs : ['tomahawk/'],
    filebase : '',
    extra_cflags : '-std=c++17',
    description : 'Tomahawk Media Player.')

libtomahawk_dep = declare_dependency(
    sources : [
        libtomahawk_qt_ui],
    link_with : libtomahawk_lib,
    include_directories : include_directories('.'))




