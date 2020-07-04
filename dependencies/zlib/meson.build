# ZLib Dependency File
#============================================================================


# Look for zlib, a required dependency.
#----------------------------------------------------
zlib_dep = declare_dependency(
    link_args : get_option('zlib_link_args'),
    dependencies : [ dependency('zlib')])


# Set HAVE_ZLIB in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_ZLIB',
    zlib_dep.found(),
    description : 'Define if the Zlib library is available.')
