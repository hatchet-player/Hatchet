# libtomahawk build file
#============================================================================


libtomahawkwidgets_dir = meson.current_source_dir()
libtomahawkwidgets_inc = [include_directories('.')]
libtomahawkwidgets_inc += tomahawk_inc


# dependancies
#============================================================================

libtomahawkwidgets_dep_list = [
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
    echonest_dep,

    libtomahawk_dep]



if (get_option('with_taglib'))
    libtomahawkwidgets_dep_list += taglib_dep
endif

if (get_option('with_liblastfm'))
    libtomahawkwidgets_dep_list += liblastfm_dep
endif

# Source files
#============================================================================


libtomahawkwidgets_src = files(
    join_paths(libtomahawkwidgets_dir, 'PlaylistDelegate.cpp'),
    join_paths(libtomahawkwidgets_dir, 'PlaylistWidget.cpp'))


libtomahawkwidgets_h = files(
        join_paths(libtomahawkwidgets_dir, 'WidgetsDllMacro.h'))


libtomahawkwidgets_moc_h = files(
    join_paths(libtomahawkwidgets_dir, 'PlaylistDelegate.h'),
    join_paths(libtomahawkwidgets_dir, 'PlaylistWidget.h'))


# Link args
#============================================================================


libtomahawkwidgets_link_list = []


libtomahawkwidgets_link_args = []


# build
#============================================================================


libtomahawkwidgets_moc = []

libtomahawkwidgets_moc += qt5.preprocess(
    moc_headers : libtomahawkwidgets_moc_h,
    include_directories : libtomahawkwidgets_inc,
    dependencies : libtomahawkwidgets_dep_list)


libtomahawkwidgets_lib = library(
    'tomahawk-widgets',
    sources : [
        libtomahawkwidgets_src,
        libtomahawkwidgets_moc],
    install : true,
    install_mode : 'rwxr-xr-x',
    install_dir : libdir,
    include_directories : libtomahawkwidgets_inc,
    link_with : libtomahawkwidgets_link_list,
    link_args : libtomahawkwidgets_link_args,
    dependencies : libtomahawkwidgets_dep_list)


install_headers(
    libtomahawkwidgets_h,
    install_dir : join_paths(includedir, ''))


libtomahawk_config = pkg.generate(
    libtomahawkwidgets_lib,
    libraries : [
        libtomahawkwidgets_lib],
    version : meson.project_version(),
    name : 'tomahawk-widgets',
    subdirs : ['tomahawk-widgets/'],
    filebase : 'tomahawk-widgets',
    extra_cflags : '-std=c++11',
    description : 'Tomahawk Widgets Library.')

    libtomahawkwidgets_dep = declare_dependency(
        link_with : libtomahawkwidgets_lib,
        include_directories : libtomahawkwidgets_inc)