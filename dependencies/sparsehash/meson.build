# Sparsehash Dependency File
#============================================================================


# Look for sparsehash, a required dependency.
#---------------------------------------------------
sparsehash_dep = declare_dependency(
    link_args : get_option('sparsehash_link_args'),
    dependencies : [ dependency(
        'libsparsehash',
        required : false,
        version : '>= 2.0.2')])

# Set HAVE_SPARSEHASH in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_SPARSEHASH',
    sparsehash_dep.found(),
    description : 'Define if the Sparsehash library is available.')