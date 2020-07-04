# libtomahawk.sip build file
#============================================================================


libtomahawk_inc += include_directories('.')
libtomahawk_sip_dir = meson.current_source_dir()


libtomahawk_src += files(
    join_paths(libtomahawk_sip_dir, 'PeerInfo.cpp'),
    join_paths(libtomahawk_sip_dir, 'SipInfo.cpp'),
    join_paths(libtomahawk_sip_dir, 'SipPlugin.cpp'),
    join_paths(libtomahawk_sip_dir, 'SipStatusMessage.cpp'))


libtomahawk_moc_h += files(
    join_paths(libtomahawk_sip_dir, 'PeerInfo.h'),
    join_paths(libtomahawk_sip_dir, 'SipInfo.h'),
    join_paths(libtomahawk_sip_dir, 'SipPlugin.h'),
    join_paths(libtomahawk_sip_dir, 'SipStatusMessage.h'))
    