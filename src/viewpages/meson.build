# viewpages build file
#============================================================================

viewpage_inc = [include_directories('.')]
viewpage_inc += libhatchet_inc 
viewpage_inc += hatchet_inc

viewpages_dirs = [
    # 'charts',
    'dashboard',
    # 'networkactivity',
    'newreleases',
    # 'whatsnew_0_8'
]


foreach dir : viewpages_dirs
    subdir(dir)
endforeach