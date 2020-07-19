# Hatchet Extra Build File
#============================================================================

hatchet_dir = meson.current_source_dir()

# build config.h
#---------------------------------------------------

config_h.set('WITH_BINARY_ATTICA', true)
config_h.set('WITH_UPOWER', true)
config_h.set('WITH_GNOMESHORTCUTHANDLER', true)

config_h = configure_file(
    input : 'Config.h.in',
    output : 'Config.h',
    configuration : config_h)


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


# install headers
#---------------------------------------------------
install_headers(
    config_h,
    install_dir : join_paths(includedir, 'hatchet'))

install_headers(
    hatchetversion_h,
    install_dir : join_paths(includedir, 'hatchet'))


# include directories
#============================================================================

hatchet_inc += include_directories('.')

# extra_dirs = [
#     'admin',
#     'lang']

# foreach dir : extra_dirs
#     subdir(dir)
# endforeach

