# tomahawk main build file
#============================================================================

tomahawk_inc += include_directories(
    '.',
    'mac',
    'xmppbot')
tomahawk_dir = meson.current_source_dir()

tomahawk_inc += viewpage_inc

# dependancies
#============================================================================


tomahawk_dep_list = [
    boost_dep,
    qca2_dep,
    qt5_dep,
    qtkeychain_dep,
    quazip_dep,
    qxt_dep,
    kf5attica_dep,
    liblucene_dep,
    libvlc_dep,
    libportfwd_dep,
    telepathy_dep,
    echonest_dep,
    single_app_guard_dep,

    libtomahawk_dep,
    libtomahawplaydarapi_dep,
    viewpage_dashboard_dep]

if (get_option('with_liblastfm')) 
    tomahawk_dep_list += liblastfm_dep
endif

# Sources
#============================================================================


tomahawk_src = files(
    join_paths(tomahawk_dir, 'AclRegistryImpl.cpp'),
    join_paths(tomahawk_dir, 'Scrobbler.cpp'),
    join_paths(tomahawk_dir, 'ShortcutHandler.cpp'),
    join_paths(tomahawk_dir, 'UbuntuUnityHack.cpp'),
    join_paths(tomahawk_dir, 'TomahawkApp.cpp'),
    join_paths(tomahawk_dir, 'main.cpp'))


tomahawk_gui_src = files(
    join_paths(tomahawk_dir, 'TomahawkTrayIcon.cpp'),
    join_paths(tomahawk_dir, 'AudioControls.cpp'),
    join_paths(tomahawk_dir, 'TomahawkWindow.cpp'))


tomahawk_moc_src = files()


tomahawk_moc_h = files(
    join_paths(tomahawk_dir, 'Scrobbler.h'),
    join_paths(tomahawk_dir, 'AclRegistryImpl.h'),
    join_paths(tomahawk_dir, 'ShortcutHandler.h'),
    join_paths(tomahawk_dir, 'UbuntuUnityHack.h'),
    join_paths(tomahawk_dir, 'TomahawkApp.h'),
    join_paths(tomahawk_dir, 'TomahawkTrayIcon.h'),
    join_paths(tomahawk_dir, 'AudioControls.h'),
    join_paths(tomahawk_dir, 'TomahawkWindow.h'))


tomahawk_moc_ui = files(
    join_paths(tomahawk_dir, 'AudioControls.ui'),
    join_paths(tomahawk_dir, 'TomahawkWindow.ui'))


tomahawk_moc_resources = files(
    join_paths(meson.source_root(), 'resources.qrc'))


tomahawk_dbus_xml = []


tomahawk_dirs = [
    'dialogs',
    'linux',
    # 'mac',
    'sourcetree',
    'widgets',
    # 'xmppbot'
]


foreach dir : tomahawk_dirs
    subdir(dir)
endforeach


# Link args
#=================================w===========================================


tomahawk_src += tomahawk_gui_src

tomahawk_link_list = [
    libtomahawk_telepathy_lib,
    ] #viewpage_dashboard_lib]


tomahawk_link_args = []


# Build
#============================================================================


tomahawk_moc = qt5.preprocess(
    moc_sources : tomahawk_moc_src,
    moc_headers : tomahawk_moc_h,
    ui_files : tomahawk_moc_ui,
    qresources : tomahawk_moc_resources,
    include_directories : tomahawk_inc,
    dependencies : tomahawk_dep_list )


tomahawk_bin = executable(
    'tomahawk',
    install : true,
    install_mode : 'rwxr-xr-x',
    install_dir : bindir,
    include_directories : tomahawk_inc,
    sources : [
        tomahawk_src,
        tomahawk_moc ],
    link_with : tomahawk_link_list,
    link_args : tomahawk_link_args,
    dependencies : tomahawk_dep_list )