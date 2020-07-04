# Tomahawk Extra Build File
#============================================================================

tomahawk_inc += include_directories('.')
tomahawk_dir = meson.current_source_dir()

# build config.h
#---------------------------------------------------

config_h.set('WITH_BINARY_ATTICA', true)
config_h.set('WITH_UPOWER', true)
config_h.set('WITH_GNOMESHORTCUTHANDLER', true)
#  #undef QTSPARKLE_FOUND */
#  #undef TOMAHAWK_FINEGRAINED_MESSAGES */
#  #undef COMPLEX_TAGLIB_FILENAME */
#  #define HAVE_VLC_ALBUMARTIST
#  #define HAVE_X11

config_h = configure_file(
    output : 'config.h',
    configuration : config_h)

add_project_arguments('-include', 'extra/config.h', language : 'cpp')


# build HatchetVersion.h
#---------------------------------------------------
version_hh = configuration_data()
version_hh.set_quoted('TOMAHAWK_ORGANIZATION_NAME', tomahawk_organization_name)
version_hh.set_quoted('TOMAHAWK_ORGANIZATION_DOMAIN', tomahawk_organization_domain)
version_hh.set_quoted('TOMAHAWK_APPLICATION_NAME', tomahawk_application_name)
version_hh.set_quoted('TOMAHAWK_TARGET_NAME', tomahawk_target_name)
version_hh.set_quoted('TOMAHAWK_BASE_TARGET_NAME', tomahawk_base_target_name)
version_hh.set_quoted('TOMAHAWK_APPLICATION_PACKAGE_NAME', tomahawk_application_package_name)
version_hh.set_quoted('TOMAHAWK_VERSION', meson.project_version())
version_hh.set_quoted('TOMAHAWK_SYSTEM', tomahawk_system)

tomahawkversion_h = configure_file(
    input : 'HatchetVersion.h.in',
    output : 'HatchetVersion.h',
    configuration : version_hh)

add_project_arguments('-include', 'extra/HatchetVersion.h', language : 'cpp')


# install headers
#---------------------------------------------------
install_headers(
    config_h,
    install_dir : join_paths(includedir, 'tomahawk'))

install_headers(
    tomahawkversion_h,
    install_dir : join_paths(includedir, 'tomahawk'))

