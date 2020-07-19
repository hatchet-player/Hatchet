# libhatchet build file
#============================================================================


libhatchet_dir = meson.current_source_dir()
libhatchet_inc = [include_directories('.')]
libhatchet_inc += hatchet_inc


# dependancies
#============================================================================

libhatchet_dep_list = [
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
    libhatchet_dep_list += taglib_dep
endif

if (get_option('with_liblastfm'))
    libhatchet_dep_list += liblastfm_dep
endif

# src
#============================================================================


libhatchet_src = files(
    join_paths(libhatchet_dir, 'EchonestCatalogSynchronizer.cpp'),
    join_paths(libhatchet_dir, 'HatchetSettings.cpp'),
    join_paths(libhatchet_dir, 'SourceList.cpp'),
    join_paths(libhatchet_dir, 'Pipeline.cpp'),
    join_paths(libhatchet_dir, 'Artist.cpp'),
    join_paths(libhatchet_dir, 'ArtistPlaylistInterface.cpp'),
    join_paths(libhatchet_dir, 'Album.cpp'),
    join_paths(libhatchet_dir, 'AlbumPlaylistInterface.cpp'),
    join_paths(libhatchet_dir, 'CountryUtils.cpp'),
    join_paths(libhatchet_dir, 'FuncTimeout.cpp'),
    join_paths(libhatchet_dir, 'Playlist.cpp'),
    join_paths(libhatchet_dir, 'PlaylistEntry.cpp'),
    join_paths(libhatchet_dir, 'PlaylistPlaylistInterface.cpp'),
    join_paths(libhatchet_dir, 'MetaPlaylistInterface.cpp'),
    join_paths(libhatchet_dir, 'Query.cpp'),
    join_paths(libhatchet_dir, 'Result.cpp'),
    join_paths(libhatchet_dir, 'Source.cpp'),
    join_paths(libhatchet_dir, 'Track.cpp'),
    join_paths(libhatchet_dir, 'TrackData.cpp'),
    join_paths(libhatchet_dir, 'SourcePlaylistInterface.cpp'),
    join_paths(libhatchet_dir, 'PlaylistInterface.cpp'),
    join_paths(libhatchet_dir, 'UrlHandler.cpp'))


libhatchet_gui_src = files(
    join_paths(libhatchet_dir, 'ActionCollection.cpp'),
    join_paths(libhatchet_dir, 'ContextMenu.cpp'),
    join_paths(libhatchet_dir, 'DownloadManager.cpp'),
    join_paths(libhatchet_dir, 'DownloadJob.cpp'),
    join_paths(libhatchet_dir, 'DropJob.cpp'),
    join_paths(libhatchet_dir, 'GlobalActionManager.cpp'),
    join_paths(libhatchet_dir, 'ViewPage.cpp'),
    join_paths(libhatchet_dir, 'ViewPageLazyLoader.cpp'),
    join_paths(libhatchet_dir, 'ViewPagePlugin.cpp'),
    join_paths(libhatchet_dir, 'ViewManager.cpp'),
    join_paths(libhatchet_dir, 'LatchManager.cpp'))


libhatchet_obj_src = files()


libhatchet_moc_src = files()


libhatchet_h = files()


libhatchet_moc_h = files(
    join_paths(libhatchet_dir, 'ActionCollection.h'),
    join_paths(libhatchet_dir, 'Album.h'),
    join_paths(libhatchet_dir, 'AlbumPlaylistInterface.h'),
    join_paths(libhatchet_dir, 'Artist.h'),
    join_paths(libhatchet_dir, 'ArtistPlaylistInterface.h'),
    join_paths(libhatchet_dir, 'AtticaManager.h'),
    join_paths(libhatchet_dir, 'ContextMenu.h'),
    join_paths(libhatchet_dir, 'DownloadJob.h'),
    join_paths(libhatchet_dir, 'DownloadManager.h'),
    join_paths(libhatchet_dir, 'DropJob.h'),
    join_paths(libhatchet_dir, 'EchonestCatalogSynchronizer.h'),
    join_paths(libhatchet_dir, 'FuncTimeout.h'),
    join_paths(libhatchet_dir, 'GlobalActionManager.h'),
    join_paths(libhatchet_dir, 'LatchManager.h'),
    join_paths(libhatchet_dir, 'MetaPlaylistInterface.h'),
    join_paths(libhatchet_dir, 'Pipeline.h'),
    join_paths(libhatchet_dir, 'PlaylistEntry.h'),
    join_paths(libhatchet_dir, 'Playlist.h'),
    join_paths(libhatchet_dir, 'PlaylistInterface.h'),
    join_paths(libhatchet_dir, 'PlaylistPlaylistInterface.h'),
    join_paths(libhatchet_dir, 'Query.h'),
    join_paths(libhatchet_dir, 'Result.h'),
    join_paths(libhatchet_dir, 'Source.h'),
    join_paths(libhatchet_dir, 'SourceList.h'),
    join_paths(libhatchet_dir, 'SourcePlaylistInterface.h'),
    join_paths(libhatchet_dir, 'HatchetSettings.h'),
    join_paths(libhatchet_dir, 'TrackData.h'),
    join_paths(libhatchet_dir, 'Track.h'),
    join_paths(libhatchet_dir, 'UrlHandler_p.h'),
    join_paths(libhatchet_dir, 'ViewManager.h'),
    join_paths(libhatchet_dir, 'ViewPagePlugin.h'))


libhatchet_moc_ui = files()


libhatchet_dirs = [
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


foreach dir : libhatchet_dirs
    subdir(dir)
endforeach


if (kf5attica_dep.found())
    libhatchet_gui_src += files(
        join_paths(libhatchet_dir, 'AtticaManager.cpp'))
endif



# Build args
#============================================================================


libhatchet_link_list = [
    libhatchet_telepathy_lib]


libhatchet_link_args = []


if (get_option('with_gui'))
    libhatchet_src += libhatchet_gui_src
endif

if (sys_name.contains('darwin'))
    libhatchet_src += libhatchet_obj_src
endif


# build
#============================================================================


libhatchet_qt_src = qt5.preprocess(
    moc_sources : libhatchet_moc_src,
    include_directories : libhatchet_inc,
    dependencies : libhatchet_dep_list)

libhatchet_qt_ui = qt5.preprocess(
    ui_files : libhatchet_moc_ui,
    include_directories : libhatchet_inc,
    dependencies : libhatchet_dep_list)

libhatchet_qt_h = qt5.preprocess(
    moc_headers : libhatchet_moc_h,
    include_directories : libhatchet_inc,
    dependencies : libhatchet_dep_list)


libhatchet_lib = shared_library(
    'hatchet',
    sources : [
        libhatchet_src,
        libhatchet_qt_src,
        libhatchet_qt_ui,
        libhatchet_qt_h],
    install : true,
    install_mode : 'rwxr-xr-x',
    install_dir : libdir,
    include_directories : libhatchet_inc,
    link_with : libhatchet_link_list,
    link_args : libhatchet_link_args,
    dependencies : libhatchet_dep_list)


install_headers(
    libhatchet_h,
    install_dir : join_paths(includedir, ''))


libhatchet_config = pkg.generate(
    libhatchet_lib,
    libraries : [],
    version : meson.project_version(),
    name : 'Hatchet',
    subdirs : ['hatchet/'],
    filebase : '',
    extra_cflags : '-std=c++17',
    description : 'Hatchet Media Player.')

libhatchet_dep = declare_dependency(
    sources : [
        libhatchet_qt_ui],
    link_with : libhatchet_lib,
    include_directories : include_directories('.'))




