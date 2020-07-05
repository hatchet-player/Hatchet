# libhatchet.accounts.configstorage.telepathy build file
#============================================================================

libhatchet_inc += include_directories('.')
telepathy_dir = meson.current_source_dir()

single_app_guard_src = files(
    join_paths(telepathy_dir, 'TelepathyConfigStorage.cpp'),
    join_paths(telepathy_dir, 'TelepathyConfigStorageConfigWidgetPlugin.cpp'))



# dependancies
#============================================================================

libhatchet_telepathy_dep_list = [
    qt5_dep]


# build
#============================================================================

libhatchet_telepathy_lib = library(
    'hatchettelepathy',
    dependencies : libhatchet_telepathy_dep_list,
)

libhatchet_telepathy_dep = declare_dependency(
    link_with : libhatchet_telepathy_lib,
    include_directories : include_directories('.')
)