# LibVLC Dependency File
#============================================================================


# Look for libvlc, a required dependency.
#---------------------------------------------------
libvlc_dep = declare_dependency(
    link_args : get_option('libvlc_link_args'),
    dependencies : [ 
        dependency('libvlc',
        version : '>= 2.1.0')])


# Set HAVE_LIBVLC in config.h
#---------------------------------------------------  
if (libvlc_dep.found())
    config_h.set(
        'HAVE_LIBVLC',
        libvlc_dep.found(),
        description : 'Define if libvls is available.')
endif
