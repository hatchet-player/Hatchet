# libtomahawk.mac build file
#============================================================================

libtomahawk_inc += include_directories('.')
libtomahawk_mac_dir = meson.current_source_dir()


if (sys_name.contains('darwin'))
    libtomahawk_src += files(
        join_paths(libtomahawk_mac_dir, 'FileHelpers.mm'))
endif