# libhatchet build file
#============================================================================

libhatchet_inc += include_directories('.')


thirdparty_dirs = []


#if (sys_name.contains('darwin'))
  thirdparty_dirs += 'Qocoa'
#endif


foreach dir : thirdparty_dirs
    subdir(dir)
endforeach


