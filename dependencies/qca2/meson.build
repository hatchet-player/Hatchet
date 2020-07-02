# LibVLC Dependency File
#============================================================================


# Look for QCA2-qt, a required dependency.
#---------------------------------------------------
qca2_dep = declare_dependency(
    link_args : get_option('qca2_link_args'),
    dependencies : [ dependency(
        'qca2-qt5',
        version : '>= 2.3.0')])


# Set HAVE_QCA2 in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_QCA2',
    qca2_dep.found(),
    description : 
        'Provides encryption and signing functions necessary for ' + 
        'some resolvers and accounts')
        