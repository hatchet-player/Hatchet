# QuaZip Dependency File
#============================================================================


# Look for quazip, a required dependency.
#---------------------------------------------------
quazip_dep = declare_dependency(
    link_args : get_option('quazip_link_args'),
    dependencies : [ 
        dependency('quazip',
        # version : '>= 0.4.3')])
        )])


# Set HAVE_QUAZIP in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_QUAZIP',
    quazip_dep.found(),
    description : 'Define if the QuaZip library is available.')
    