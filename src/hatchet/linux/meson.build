# hatchet.linux build file
#============================================================================

hatchet_linux_dir = meson.current_source_dir()
hatchet_inc += include_directories('.')

# Sources
#============================================================================

hatchet_gui_src += files(
    join_paths(hatchet_linux_dir, 'UPowerHandler.cpp'),
    join_paths(hatchet_linux_dir, 'GnomeShortcutHandler.cpp'))


hatchet_moc_h += files(
    join_paths(hatchet_linux_dir, 'UPowerHandler.h'),
    join_paths(hatchet_linux_dir, 'GnomeShortcutHandler.h'))

    
hatchet_dbus_xml += [
    [
        files(join_paths(hatchet_linux_dir, 'org.freedesktop.UPower.xml')),
        'UPowerProxy' ],
    [
        files(join_paths(hatchet_linux_dir, 'GnomeSettingsDaemonMediaKeys.xml')),
        'GnomeSettingsDaemonMediaKeysProxy' ]
]

# Targets
#============================================================================


foreach x : hatchet_dbus_xml
    run_command(
        qdbusxml2cpp,
        '-m','-p',
        x[1],
        x[0])
    
    cpp_file = files(
        join_paths(hatchet_linux_dir, '@0@.cpp'.format(x[1])))

    h_file = files(
        join_paths(hatchet_linux_dir, '@0@.h'.format(x[1])))
    
    hatchet_src += cpp_file

    hatchet_moc_src += cpp_file

    hatchet_moc_h += h_file

endforeach

