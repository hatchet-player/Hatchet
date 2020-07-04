# QT Keychain Dependency File
#============================================================================


# Look for QtKeychain, a required dependency.
#---------------------------------------------------
qtkeychain_dep = declare_dependency(
    dependencies : [
        cpp.find_library('qt5keychain')])


# Set HAVE_QTKEYCHAIN in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_QTKEYCHAIN',
    qtkeychain_dep.found(),
    description : '')
    