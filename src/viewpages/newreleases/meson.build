# hatchet.linux build file
#============================================================================


viewpage_newreleases_dir = meson.current_source_dir()
viewpage_newreleases_inc = [include_directories('.')]
viewpage_newreleases_inc += viewpage_inc 


# create target name for convenience
target='@0@_viewpage_newreleases'.format(hatchet_base_target_name)

# Dependencies
#============================================================================

viewpage_newreleases_dep_list = [
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
    taglib_dep,

    libhatchet_dep,
    libhatchetwidgets_dep]


# Sources
#============================================================================


viewpage_newreleases_src = files(
    join_paths(viewpage_newreleases_dir, 'NewReleasesWidget.cpp'))


viewpage_newreleases_moc_h = files(
    join_paths(viewpage_newreleases_dir, 'NewReleasesWidget.h'))


viewpage_newreleases_moc_ui = files(
    join_paths(viewpage_newreleases_dir, 'NewReleasesWidget.ui'))



# Link args
#============================================================================

viewpage_newreleases_link_list = []


viewpage_newreleases_link_args = []


# Build
#============================================================================


viewpage_newreleases_moc = qt5.preprocess(
    moc_headers : viewpage_newreleases_moc_h,
    ui_files : viewpage_newreleases_moc_ui,
    include_directories : viewpage_newreleases_inc,
    dependencies : viewpage_newreleases_dep_list )


viewpage_newreleases_lib = library(
    target,
    sources : [
        viewpage_newreleases_src,
        viewpage_newreleases_moc],
    install_mode : 'rwxr-xr-x',
    install_dir : libdir,
    include_directories : viewpage_newreleases_inc,
    link_with : viewpage_newreleases_link_list,
    link_args : viewpage_newreleases_link_args,
    dependencies : viewpage_newreleases_dep_list)


viewpage_newreleases_dep = declare_dependency(
    link_with : viewpage_newreleases_lib,
    include_directories : viewpage_newreleases_inc)