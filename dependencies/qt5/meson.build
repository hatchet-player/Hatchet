# QT5 Dependency File
#============================================================================


# declare QT5 Modules
#---------------------------------------------------
qt5_link_args = get_option('qt5_link_args')
qt5_mod_list = [
    'Core',
    'Concurrent',
    'Gui',
    'Network',
    'Sql',
    'Svg',
    'UiTools',
    'WebEngineWidgets',
    'Widgets',
    'Xml',
    'DBus']


# Check if X11Extras module is present
#---------------------------------------------------
message('checking if Qt5 X11 Extras is present')
check_qt5_x11 = dependency(
    'qt5', modules : 'X11Extras', required : false)


if (check_qt5_x11.found())
    qt5_mod_list += 'X11Extras'
    qt5_link_args += get_option('qt5_x11_link_args')
endif


# Look for qt5, a required dependency.
#---------------------------------------------------
qt5_dep = declare_dependency(
    link_args : qt5_link_args,
    dependencies : [ dependency(
        'qt5',
        modules: qt5_mod_list)])


# qdbusxml2cpp converts qt dbus files to cpp sources
#---------------------------------------------------
qdbusxml2cpp = find_program('qdbusxml2cpp', required : true)


# Set HAVE_QT5_X11 in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_QT5_X11', 
    check_qt5_x11.found(),
    description : 'Whether to build with QT5 X11 support')


# Set HAVE_QT5 in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_QT5', 
    qt5_dep.found(),
    description : '')
