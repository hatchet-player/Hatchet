# Boost Dependency File
#============================================================================


# Look for boost, a required dependency.
#----------------------------------------------------
boost_mod_list = [
        'system',
        'context',
        'coroutine',
        'filesystem',
        'iostreams',
        'regex',
        'thread']

boost_dep = declare_dependency(
    link_args : get_option('boost_link_args'),
    dependencies : [ dependency(
        'boost',
        modules: boost_mod_list)])


# Set HAVE_BOOST in config.h
#---------------------------------------------------
config_h.set(
    'HAVE_BOOST',
    boost_dep.found(),
    description : 'Define if the Boost library is available.')
    