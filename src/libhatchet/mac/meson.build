# libhatchet.mac build file
#============================================================================

libhatchet_inc += include_directories('.')
libhatchet_mac_dir = meson.current_source_dir()


if (sys_name.contains('darwin'))
    libhatchet_src += files(
        join_paths(libhatchet_mac_dir, 'FileHelpers.mm'))
endif