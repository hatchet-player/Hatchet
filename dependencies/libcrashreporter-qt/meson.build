# LibCrashReporter-Qt Dependency File
#============================================================================

    
# check if libcrashreporter-qt is already installed
#---------------------------------------------------
qt_crashreporter_dep = dependency('libcrashreporter-qt', required : false)


# If not, include the submodule
#---------------------------------------------------
if not (qt_crashreporter_dep.found())
    qt_crashreporter_proj = subproject('libcrashreporter-qt')
    qt_crashreporter_dep = qt_crashreporter_proj.get_variable('qt_crashreporter_dep')
endif


# Set HAVE_CRASHREPORTER in config.h
#---------------------------------------------------   
config_h.set(
    'HAVE_CRASHREPORTER',
    echonest_dep.found(),
    description : '')
