# Qxt dependency file
#============================================================================


# check if  qt-certificate-addon is already installed
#---------------------------------------------------
qxt_dep = dependency('qxt', required : false)


# If not, include the submodule
#---------------------------------------------------
if not qxt_dep.found()
  qxt_proj = subproject('qxtweb-standalone')
  qxt_dep = declare_dependency(
    link_with : qxt_proj.get_variable('libqxt_lib'),
    include_directories : qxt_proj.get_variable('libqxt_inc'))
endif


# Set HAVE_qxt in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_QXT',
    qxt_dep.found(),
    description : '')
