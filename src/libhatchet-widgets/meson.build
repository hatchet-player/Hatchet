# libhatchet build file
#============================================================================


libhatchetwidgets_dir = meson.current_source_dir()
libhatchetwidgets_inc = [include_directories('.')]
libhatchetwidgets_inc += hatchet_inc


# dependancies
#============================================================================

libhatchetwidgets_dep_list = [
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

    libhatchet_dep]



if (get_option('with_taglib'))
    libhatchetwidgets_dep_list += taglib_dep
endif

if (get_option('with_liblastfm'))
    libhatchetwidgets_dep_list += liblastfm_dep
endif

# Source files
#============================================================================


libhatchetwidgets_src = files(
    join_paths(libhatchetwidgets_dir, 'PlaylistDelegate.cpp'),
    join_paths(libhatchetwidgets_dir, 'PlaylistWidget.cpp'))


libhatchetwidgets_h = files(
        join_paths(libhatchetwidgets_dir, 'WidgetsDllMacro.h'))


libhatchetwidgets_moc_h = files(
    join_paths(libhatchetwidgets_dir, 'PlaylistDelegate.h'),
    join_paths(libhatchetwidgets_dir, 'PlaylistWidget.h'))


# Link args
#============================================================================


libhatchetwidgets_link_list = []


libhatchetwidgets_link_args = []


# build
#============================================================================


libhatchetwidgets_moc = []

libhatchetwidgets_moc += qt5.preprocess(
    moc_headers : libhatchetwidgets_moc_h,
    include_directories : libhatchetwidgets_inc,
    dependencies : libhatchetwidgets_dep_list)


libhatchetwidgets_lib = library(
    'hatchet-widgets',
    sources : [
        libhatchetwidgets_src,
        libhatchetwidgets_moc],
    install : true,
    install_mode : 'rwxr-xr-x',
    install_dir : libdir,
    include_directories : libhatchetwidgets_inc,
    link_with : libhatchetwidgets_link_list,
    link_args : libhatchetwidgets_link_args,
    dependencies : libhatchetwidgets_dep_list)


install_headers(
    libhatchetwidgets_h,
    install_dir : join_paths(includedir, ''))


libhatchet_config = pkg.generate(
    libhatchetwidgets_lib,
    libraries : [
        libhatchetwidgets_lib],
    version : meson.project_version(),
    name : 'hatchet-widgets',
    subdirs : ['hatchet-widgets/'],
    filebase : 'hatchet-widgets',
    extra_cflags : '-std=c++11',
    description : 'Hatchet Widgets Library.')

    libhatchetwidgets_dep = declare_dependency(
        link_with : libhatchetwidgets_lib,
        include_directories : libhatchetwidgets_inc)