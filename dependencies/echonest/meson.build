# Echo-Nest dependency File
#============================================================================

# Look for echonest, an optional dependency. (should be, not atm)
#---------------------------------------------------
if (get_option('with_echonest'))
    echonest_dep = declare_dependency(
        link_args : get_option('echonest_link_args'),
        dependencies : dependency(
            'libechonest5',
            version : '>= 2.3.1'))
else
    echonest_dep = disabler()
endif

# Set HAVE_ECHONEST in config.h
#---------------------------------------------------   
config_h.set(
        'HAVE_ECHONEST',
        echonest_dep.found(),
        description : 'echonest is needed for intefacing with Echo Nest')
