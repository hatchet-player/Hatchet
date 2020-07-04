# tomahawk.linux build file
#============================================================================

tomahawk_linux_dir = meson.current_source_dir()
tomahawk_inc += include_directories('.')

# Sources
#============================================================================

tomahawk_gui_src += files(
    join_paths(tomahawk_linux_dir, 'UPowerHandler.cpp'),
    join_paths(tomahawk_linux_dir, 'GnomeShortcutHandler.cpp'))


tomahawk_moc_h += files(
    join_paths(tomahawk_linux_dir, 'UPowerHandler.h'),
    join_paths(tomahawk_linux_dir, 'GnomeShortcutHandler.h'))

    
tomahawk_dbus_xml += [
    [
        files(join_paths(tomahawk_linux_dir, 'org.freedesktop.UPower.xml')),
        'UPowerProxy' ],
    [
        files(join_paths(tomahawk_linux_dir, 'GnomeSettingsDaemonMediaKeys.xml')),
        'GnomeSettingsDaemonMediaKeysProxy' ]
]

# Targets
#============================================================================


foreach x : tomahawk_dbus_xml
    run_command(
        qdbusxml2cpp,
        '-m','-p',
        x[1],
        x[0])
    
    cpp_file = files(
        join_paths(tomahawk_linux_dir, '@0@.cpp'.format(x[1])))

    h_file = files(
        join_paths(tomahawk_linux_dir, '@0@.h'.format(x[1])))
    
    tomahawk_src += cpp_file

    tomahawk_moc_src += cpp_file

    tomahawk_moc_h += h_file

endforeach

