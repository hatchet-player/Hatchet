# src build file
#============================================================================

tomahawk_inc += include_directories('.')

src_dirs = [
    'libtomahawk',
    'libtomahawk-widgets',
    'libtomahawk-playdarapi',
    # 'accounts',
    # 'infoplugins',
    'viewpages',
    'tomahawk'
]

if (get_option('with_tools'))
    src_dirs += 'tools'
endif


if (get_option('with_crashreporter'))
    src_dirs += 'crashreporter'
endif


if (get_option('with_tests'))
    src_dirs += 'tests'
endif


foreach dir : src_dirs
    subdir(dir)
endforeach





