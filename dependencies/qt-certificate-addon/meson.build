# Qt5 Certificate Addon Dependency File
#============================================================================


# check if  qt-certificate-addon is already installed
#---------------------------------------------------
qtcertaddon_dep = dependency('qt-certificate-addon', required : false)


# If not, include the submodule
#---------------------------------------------------
if not qtcertaddon_dep.found()
  qtcertaddon_proj = subproject('qt-certificate-addon')
  qtcertaddon_dep = declare_dependency(
    link_with : qtcertaddon_proj.get_variable('qtcertaddon_lib'),
    include_directories : qtcertaddon_proj.get_variable('qtcertaddon_inc'))
endif


# Set HAVE_QTCERTADDON in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_QTCERTADDON',
    qtcertaddon_dep.found(),
    description : '')
