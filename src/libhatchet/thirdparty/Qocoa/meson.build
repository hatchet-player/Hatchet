# libhatchet.thirdparty.Qocoa build file
#============================================================================

libhatchet_inc += include_directories('.')
libhatchet_thirdparty_qocoa_dir = meson.current_source_dir()


libhatchet_src += files(
    join_paths(libhatchet_thirdparty_qocoa_dir, 'qbutton.cpp'),
    join_paths(libhatchet_thirdparty_qocoa_dir, 'qsearchfield.cpp'),
    join_paths(libhatchet_thirdparty_qocoa_dir, 'qtoolbartabdialog.cpp'))


libhatchet_moc_src += files(
    join_paths(libhatchet_thirdparty_qocoa_dir, 'qsearchfield.cpp'),
    join_paths(libhatchet_thirdparty_qocoa_dir, 'qtoolbartabdialog.cpp'))


libhatchet_moc_h += files(
    join_paths(libhatchet_thirdparty_qocoa_dir, 'qbutton.h'),
    join_paths(libhatchet_thirdparty_qocoa_dir, 'qtoolbartabdialog.h'),
    join_paths(libhatchet_thirdparty_qocoa_dir, 'qsearchfield.h'))


if (sys_name.contains('darwin'))
    libhatchet_src += files(
        join_paths(libhatchet_thirdparty_qocoa_dir, 'qbutton_mac.mm'),
        join_paths(libhatchet_thirdparty_qocoa_dir, 'qsearchfield_mac.mm'))
endif