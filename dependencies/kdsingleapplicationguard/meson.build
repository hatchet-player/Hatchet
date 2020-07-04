# KDSingleApplicationGuard build file
#============================================================================


# check if
# KDSingleApplicationGuard is already installed
#---------------------------------------------------
kdasingle_dep = dependency('kdsingleapplicationguard', required : false)


# If not, include the submodule
#---------------------------------------------------
if not kdasingle_dep.found()
  kdasingle_proj = subproject('kdsingleapplicationguard')
  single_app_guard_dep = declare_dependency(
    link_with : kdasingle_proj.get_variable('single_app_guard_lib'),
    include_directories : kdasingle_proj.get_variable('kdsingle_inc'))
endif


# Set HAVE_KDSINGLEAPPLICATIONGUARD in config.h
#---------------------------------------------------
config_h.set(
    'HAVE_KDSINGLEAPPLICATIONGUARD',
    kdasingle_dep.found(),
    description : '')
