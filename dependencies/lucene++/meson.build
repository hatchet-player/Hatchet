# Lucene++ Dependency File
#============================================================================

# Look for lucene++, a required dependency.
#---------------------------------------------------
liblucene_dep = declare_dependency(
    link_args : get_option('kf5attica_link_args'),
    dependencies : [ dependency(
        'liblucene++',
        version : '>= 3.0.6')])


# Set HAVE_LIBLUCENE in config.h
#---------------------------------------------------  
if (liblucene_dep.found())
    config_h.set(
        'HAVE_LIBLUCENE',
        liblucene_dep.found(),
        description : 
            'Lucene++ is an open-source C++ search engine')
endif
