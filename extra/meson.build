# Hatchet Extra Build File
#============================================================================

hatchet_inc += include_directories('.')
hatchet_dir = meson.current_source_dir()

# build config.h
#---------------------------------------------------

config_h.set('WITH_BINARY_ATTICA', true)
config_h.set('WITH_UPOWER', true)
config_h.set('WITH_GNOMESHORTCUTHANDLER', true)
#  #undef QTSPARKLE_FOUND */
#  #undef HATCHET_FINEGRAINED_MESSAGES */
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
version_hh.set_quoted('HATCHET_ORGANIZATION_NAME', hatchet_organization_name)
version_hh.set_quoted('HATCHET_ORGANIZATION_DOMAIN', hatchet_organization_domain)
version_hh.set_quoted('HATCHET_APPLICATION_NAME', hatchet_application_name)
version_hh.set_quoted('HATCHET_TARGET_NAME', hatchet_target_name)
version_hh.set_quoted('HATCHET_BASE_TARGET_NAME', hatchet_base_target_name)
version_hh.set_quoted('HATCHET_APPLICATION_PACKAGE_NAME', hatchet_application_package_name)
version_hh.set_quoted('HATCHET_VERSION', meson.project_version())
version_hh.set_quoted('HATCHET_SYSTEM', hatchet_system)

hatchetversion_h = configure_file(
    input : 'HatchetVersion.h.in',
    output : 'HatchetVersion.h',
    configuration : version_hh)

add_project_arguments('-include', 'extra/HatchetVersion.h', language : 'cpp')


# install headers
#---------------------------------------------------
install_headers(
    config_h,
    install_dir : join_paths(includedir, 'hatchet'))

install_headers(
    hatchetversion_h,
    install_dir : join_paths(includedir, 'hatchet'))

