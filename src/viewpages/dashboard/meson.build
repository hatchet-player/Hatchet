# tomahawk.linux build file
#============================================================================


viewpage_dashboard_dir = meson.current_source_dir()
viewpage_dashboard_inc = [include_directories('.')]
viewpage_dashboard_inc += viewpage_inc 


# create target name for convenience
target='@0@_viewpage_dashboard'.format(tomahawk_base_target_name)

# Dependencies
#============================================================================

viewpage_dashboard_dep_list = [
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

    libtomahawk_dep,
    libtomahawkwidgets_dep]


# Sources
#============================================================================


viewpage_dashboard_src = files(
    join_paths(viewpage_dashboard_dir, 'Dashboard.cpp'))


viewpage_dashboard_moc_h = files(
    join_paths(viewpage_dashboard_dir, 'Dashboard.h'))


viewpage_dashboard_moc_ui = files(
    join_paths(viewpage_dashboard_dir, 'DashboardWidget.ui'))



# Link args
#============================================================================

viewpage_dashboard_link_list = []


viewpage_dashboard_link_args = []


# Build
#============================================================================


viewpage_dashboard_moc = qt5.preprocess(
    moc_headers : viewpage_dashboard_moc_h,
    ui_files : viewpage_dashboard_moc_ui,
    include_directories : viewpage_dashboard_inc,
    dependencies : viewpage_dashboard_dep_list )


viewpage_dashboard_lib = library(
    target,
    sources : [
        viewpage_dashboard_src,
        viewpage_dashboard_moc],
    install : true,
    install_mode : 'rwxr-xr-x',
    install_dir : libdir,
    include_directories : viewpage_dashboard_inc,
    link_with : viewpage_dashboard_link_list,
    link_args : viewpage_dashboard_link_args,
    dependencies : viewpage_dashboard_dep_list)


viewpage_dashboard_dep = declare_dependency(
    link_with : viewpage_dashboard_lib,
    include_directories : viewpage_dashboard_inc)