# libtomahawk-playdarapi build file
#============================================================================


libtomahawplaydarapi_inc = [include_directories('.')]
libtomahawplaydarapi_dir = meson.current_source_dir()


# dependancies
#============================================================================

libtomahawplaydarapi_dep_list = [
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
    single_app_guard_dep,
    qtcertaddon_dep,
    qxt_dep,
    
    libtomahawk_dep]



if (get_option('with_taglib'))
    libtomahawplaydarapi_dep_list += taglib_dep
endif

if (get_option('with_liblastfm'))
    libtomahawplaydarapi_dep_list += liblastfm_dep
endif

# Source files
#============================================================================


libtomahawplaydarapi_src = files(
    join_paths(libtomahawplaydarapi_dir, 'Api_v1_5.cpp'),
    join_paths(libtomahawplaydarapi_dir, 'Api_v1.cpp'),
    join_paths(libtomahawplaydarapi_dir, 'PlaydarApi.cpp'),
    join_paths(libtomahawplaydarapi_dir, 'StatResponseHandler.cpp'))

libtomahawplaydarapi_h = files()


libtomahawplaydarapi_moc_h = files(
    join_paths(libtomahawplaydarapi_dir, 'Api_v1_5.h'),
    join_paths(libtomahawplaydarapi_dir, 'Api_v1.h'),
    join_paths(libtomahawplaydarapi_dir, 'PlaydarApi.h'),
    join_paths(libtomahawplaydarapi_dir, 'StatResponseHandler.h'))


# Link args
#============================================================================


libtomahawk_link_list = []


libtomahawk_link_args = []


# build
#============================================================================


libtomahawplaydarapi_moc = qt5.preprocess(
    moc_headers : libtomahawplaydarapi_moc_h,
    include_directories : libtomahawk_inc,
    dependencies : libtomahawplaydarapi_dep_list)


libtomahawplaydarapi_lib = library(
    'tomahawk-playdarapi',
    sources : [
        libtomahawplaydarapi_src,
        libtomahawplaydarapi_moc],
    install : true,
    install_mode : 'rwxr-xr-x',
    install_dir : libdir,
    include_directories : libtomahawplaydarapi_inc,
    link_with : libtomahawk_link_list,
    link_args : libtomahawk_link_args,
    dependencies : libtomahawplaydarapi_dep_list)


install_headers(
    libtomahawplaydarapi_h,
    install_dir : join_paths(includedir, ''))


libtomahawplaydarapi_config = pkg.generate(
    libtomahawplaydarapi_lib,
    libraries : [
        libtomahawplaydarapi_lib],
    version : meson.project_version(),
    name : 'tomahawk-widgets',
    subdirs : ['tomahawk-widgets/'],
    filebase : 'tomahawk-widgets',
    extra_cflags : '-std=c++11',
    description : 'Tomahawk Playdar API.')


libtomahawplaydarapi_dep = declare_dependency(
    sources : [
        libtomahawplaydarapi_moc],
    link_with : libtomahawplaydarapi_lib,
    include_directories : libtomahawplaydarapi_inc)