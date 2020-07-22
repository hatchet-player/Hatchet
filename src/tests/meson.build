# test build file
#========================================================================

test_dir = meson.current_source_dir()

# include directories
#========================================================================


# add subdirectories
#---------------------------------------------------
test_dirs = [
    'TestDatabase',
    'TestQuery',
    'TestResult',
    'TestServent'
    ]


foreach dir : test_dirs
    subdir(dir)
endforeach


