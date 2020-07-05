# hatchet main build file
#============================================================================

hatchet_inc += include_directories(
    '.',
    'mac',
    'xmppbot')
hatchet_dir = meson.current_source_dir()

hatchet_inc += viewpage_inc

# dependancies
#============================================================================


hatchet_dep_list = [
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

    libhatchet_dep,
    libhatchetplaydarapi_dep,
    viewpage_dashboard_dep]

if (get_option('with_liblastfm')) 
    hatchet_dep_list += liblastfm_dep
endif

# Sources
#============================================================================


hatchet_src = files(
    join_paths(hatchet_dir, 'AclRegistryImpl.cpp'),
    join_paths(hatchet_dir, 'Scrobbler.cpp'),
    join_paths(hatchet_dir, 'ShortcutHandler.cpp'),
    join_paths(hatchet_dir, 'UbuntuUnityHack.cpp'),
    join_paths(hatchet_dir, 'HatchetApp.cpp'),
    join_paths(hatchet_dir, 'main.cpp'))


hatchet_gui_src = files(
    join_paths(hatchet_dir, 'HatchetTrayIcon.cpp'),
    join_paths(hatchet_dir, 'AudioControls.cpp'),
    join_paths(hatchet_dir, 'HatchetWindow.cpp'))


hatchet_moc_src = files()


hatchet_moc_h = files(
    join_paths(hatchet_dir, 'Scrobbler.h'),
    join_paths(hatchet_dir, 'AclRegistryImpl.h'),
    join_paths(hatchet_dir, 'ShortcutHandler.h'),
    join_paths(hatchet_dir, 'UbuntuUnityHack.h'),
    join_paths(hatchet_dir, 'HatchetApp.h'),
    join_paths(hatchet_dir, 'HatchetTrayIcon.h'),
    join_paths(hatchet_dir, 'AudioControls.h'),
    join_paths(hatchet_dir, 'HatchetWindow.h'))


hatchet_moc_ui = files(
    join_paths(hatchet_dir, 'AudioControls.ui'),
    join_paths(hatchet_dir, 'HatchetWindow.ui'))


hatchet_moc_resources = files(
    join_paths(meson.source_root(), 'resources.qrc'))


hatchet_dbus_xml = []


hatchet_dirs = [
    'dialogs',
    'linux',
    # 'mac',
    'sourcetree',
    'widgets',
    # 'xmppbot'
]


foreach dir : hatchet_dirs
    subdir(dir)
endforeach


# Link args
#=================================w===========================================


hatchet_src += hatchet_gui_src

hatchet_link_list = [
    libhatchet_telepathy_lib,
    ] #viewpage_dashboard_lib]


hatchet_link_args = []


# Build
#============================================================================


hatchet_moc = qt5.preprocess(
    moc_sources : hatchet_moc_src,
    moc_headers : hatchet_moc_h,
    ui_files : hatchet_moc_ui,
    qresources : hatchet_moc_resources,
    include_directories : hatchet_inc,
    dependencies : hatchet_dep_list )


hatchet_bin = executable(
    'hatchet',
    install : true,
    install_mode : 'rwxr-xr-x',
    install_dir : bindir,
    include_directories : hatchet_inc,
    sources : [
        hatchet_src,
        hatchet_moc ],
    link_with : hatchet_link_list,
    link_args : hatchet_link_args,
    dependencies : hatchet_dep_list )