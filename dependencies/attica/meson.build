# Attica Dependency File
#============================================================================


# Look for attica, a required dependency.
#---------------------------------------------------
kf5attica_dep = declare_dependency(
    link_args : get_option('kf5attica_link_args'),
    dependencies : [ dependency(
        'KF5Attica',
        version : '>= 5.6.0')])


# Set HAVE_KF5ATTICA in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_KF5ATTICA',
    kf5attica_dep.found(),
    description : 
        'Provides support for installation of resolvers from the' +
        'Tomahawk website')
