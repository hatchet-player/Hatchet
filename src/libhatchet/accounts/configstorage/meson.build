# libtomahawk.accounts.configstorage build file
#============================================================================

libtomahawk_inc += include_directories('.')
libtomahawk_configstorage_dirs = []

if (get_option('with_telepathy'))
    libtomahawk_configstorage_dirs += 'telepathy'
endif

foreach dir : libtomahawk_configstorage_dirs
    subdir(dir)
endforeach
