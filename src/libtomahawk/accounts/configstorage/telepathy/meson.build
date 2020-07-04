# libtomahawk.accounts.configstorage.telepathy build file
#============================================================================

libtomahawk_inc += include_directories('.')
telepathy_dir = meson.current_source_dir()

single_app_guard_src = files(
    join_paths(telepathy_dir, 'TelepathyConfigStorage.cpp'),
    join_paths(telepathy_dir, 'TelepathyConfigStorageConfigWidgetPlugin.cpp'))



# dependancies
#============================================================================

libtomahawk_telepathy_dep_list = [
    qt5_dep]


# build
#============================================================================

libtomahawk_telepathy_lib = library(
    'tomahawktelepathy',
    dependencies : libtomahawk_telepathy_dep_list,
)

libtomahawk_telepathy_dep = declare_dependency(
    link_with : libtomahawk_telepathy_lib,
    include_directories : include_directories('.')
)