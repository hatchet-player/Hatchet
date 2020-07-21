# libhatchet-playdarapi build file
#============================================================================


libhatchetplaydarapi_inc = [include_directories('.')]
libhatchetplaydarapi_dir = meson.current_source_dir()


# dependancies
#============================================================================

libhatchetplaydarapi_dep_list = [
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
    single_app_guard_dep,
    qtcertaddon_dep,
    qxt_dep,
    
    libhatchet_dep]



if (get_option('with_taglib'))
    libhatchetplaydarapi_dep_list += taglib_dep
endif

if (get_option('with_liblastfm'))
    libhatchetplaydarapi_dep_list += liblastfm_dep
endif

# Source files
#============================================================================


libhatchetplaydarapi_src = files(
    join_paths(libhatchetplaydarapi_dir, 'Api_v1_5.cpp'),
    join_paths(libhatchetplaydarapi_dir, 'Api_v1.cpp'),
    join_paths(libhatchetplaydarapi_dir, 'PlaydarApi.cpp'),
    join_paths(libhatchetplaydarapi_dir, 'StatResponseHandler.cpp'))

libhatchetplaydarapi_h = files()


libhatchetplaydarapi_moc_h = files(
    join_paths(libhatchetplaydarapi_dir, 'Api_v1_5.h'),
    join_paths(libhatchetplaydarapi_dir, 'Api_v1.h'),
    join_paths(libhatchetplaydarapi_dir, 'PlaydarApi.h'),
    join_paths(libhatchetplaydarapi_dir, 'StatResponseHandler.h'))


# Link args
#============================================================================


libhatchet_link_list = []


libhatchet_link_args = []


# build
#============================================================================


libhatchetplaydarapi_moc = qt5.preprocess(
    moc_headers : libhatchetplaydarapi_moc_h,
    include_directories : libhatchet_inc,
    dependencies : libhatchetplaydarapi_dep_list)


libhatchetplaydarapi_lib = library(
    'hatchet-playdarapi',
    sources : [
        libhatchetplaydarapi_src,
        libhatchetplaydarapi_moc],
    install : true,
    install_mode : 'rwxr-xr-x',
    install_dir : libdir,
    include_directories : libhatchetplaydarapi_inc,
    link_with : libhatchet_link_list,
    link_args : libhatchet_link_args,
    dependencies : libhatchetplaydarapi_dep_list)


install_headers(
    libhatchetplaydarapi_h,
    install_dir : join_paths(includedir, ''))


libhatchetplaydarapi_config = pkg.generate(
    libhatchetplaydarapi_lib,
    libraries : [
        libhatchetplaydarapi_lib],
    version : meson.project_version(),
    name : 'hatchet-widgets',
    subdirs : ['hatchet-widgets/'],
    filebase : 'hatchet-widgets',
    extra_cflags : '-std=c++11',
    description : 'Hatchet Playdar API.')


libhatchetplaydarapi_dep = declare_dependency(
    sources : [
        libhatchetplaydarapi_moc],
    link_with : libhatchetplaydarapi_lib,
    include_directories : libhatchetplaydarapi_inc)