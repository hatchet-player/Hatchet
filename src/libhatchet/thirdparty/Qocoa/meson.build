# libtomahawk.thirdparty.Qocoa build file
#============================================================================

libtomahawk_inc += include_directories('.')
libtomahawk_thirdparty_qocoa_dir = meson.current_source_dir()


libtomahawk_src += files(
    join_paths(libtomahawk_thirdparty_qocoa_dir, 'qbutton.cpp'),
    join_paths(libtomahawk_thirdparty_qocoa_dir, 'qsearchfield.cpp'),
    join_paths(libtomahawk_thirdparty_qocoa_dir, 'qtoolbartabdialog.cpp'))


libtomahawk_moc_src += files(
    join_paths(libtomahawk_thirdparty_qocoa_dir, 'qsearchfield.cpp'),
    join_paths(libtomahawk_thirdparty_qocoa_dir, 'qtoolbartabdialog.cpp'))


libtomahawk_moc_h += files(
    join_paths(libtomahawk_thirdparty_qocoa_dir, 'qbutton.h'),
    join_paths(libtomahawk_thirdparty_qocoa_dir, 'qtoolbartabdialog.h'),
    join_paths(libtomahawk_thirdparty_qocoa_dir, 'qsearchfield.h'))


if (sys_name.contains('darwin'))
    libtomahawk_src += files(
        join_paths(libtomahawk_thirdparty_qocoa_dir, 'qbutton_mac.mm'),
        join_paths(libtomahawk_thirdparty_qocoa_dir, 'qsearchfield_mac.mm'))
endif