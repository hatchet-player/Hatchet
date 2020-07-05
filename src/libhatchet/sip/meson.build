# libhatchet.sip build file
#============================================================================


libhatchet_inc += include_directories('.')
libhatchet_sip_dir = meson.current_source_dir()


libhatchet_src += files(
    join_paths(libhatchet_sip_dir, 'PeerInfo.cpp'),
    join_paths(libhatchet_sip_dir, 'SipInfo.cpp'),
    join_paths(libhatchet_sip_dir, 'SipPlugin.cpp'),
    join_paths(libhatchet_sip_dir, 'SipStatusMessage.cpp'))


libhatchet_moc_h += files(
    join_paths(libhatchet_sip_dir, 'PeerInfo.h'),
    join_paths(libhatchet_sip_dir, 'SipInfo.h'),
    join_paths(libhatchet_sip_dir, 'SipPlugin.h'),
    join_paths(libhatchet_sip_dir, 'SipStatusMessage.h'))
    