# libhatchet.accounts.configstorage build file
#============================================================================

libhatchet_inc += include_directories('.')
libhatchet_configstorage_dirs = []

if (get_option('with_telepathy'))
    libhatchet_configstorage_dirs += 'telepathy'
endif

foreach dir : libhatchet_configstorage_dirs
    subdir(dir)
endforeach
