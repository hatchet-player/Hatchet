# LibLastFM dependency file
#============================================================================

# Look for liblastfm, an optional dependency. (should be, not atm)
#---------------------------------------------------
if (get_option('with_liblastfm'))    
    liblastfm_dep = declare_dependency(
        dependencies : [cpp.find_library('lastfm5')],
        link_args : get_option('liblastfm_link_args'))    

    if not (cpp.has_header('lastfm5/Track.h'))
        error('LibLastFM version too low. Track.h not found')
    endif
else
    liblastfm_dep = disabler()
endif


# Set HAVE_LIBLASTFM in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_LIBLASTFM',
    liblastfm_dep.found(),
    description : 'liblastfm is needed for reading meta data from ' +
    'audio files.')
    