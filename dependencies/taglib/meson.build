# Taglib dependency File
#============================================================================


# Look for taglib, an optional dependency. (should be, not atm)
#---------------------------------------------------
if (get_option('with_taglib'))
    taglib_dep = declare_dependency(
        link_args : get_option('taglib_link_args'),
        dependencies : dependency(
            'taglib',
            version : '>= 1.9'))
else
    taglib_dep = disabler()
endif


# Set HAVE_TAGLIB in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_TAGLIB',
    taglib_dep.found(),
    description : 'taglib is needed for reading meta data from' +
    'audio files.')
    