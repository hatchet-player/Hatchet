# Libportfwd dependency file
#============================================================================

# check if libportfwd is already installed
#---------------------------------------------------
libportfwd_dep = dependency('libportfwd', required : false)

# If not, include the submodule
#---------------------------------------------------
if not (libportfwd_dep.found())
  libportfwd_proj = subproject('libportfwd')
  libportfwd_dep = declare_dependency(
    link_with : libportfwd_proj.get_variable('libportfwd_lib'),
    include_directories : libportfwd_proj.get_variable('libportfwd_inc'))
endif
