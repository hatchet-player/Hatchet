# libhatchet network file
#============================================================================


libhatchet_inc += include_directories('.', 'acl')
libhatchet_network_dir = meson.current_source_dir()

libhatchet_src += files(
    join_paths(libhatchet_network_dir, 'acl/AclRegistry.cpp'),
    join_paths(libhatchet_network_dir, 'acl/AclRequest.cpp'),
    join_paths(libhatchet_network_dir, 'BufferIoDevice.cpp'),
    join_paths(libhatchet_network_dir, 'Msg.cpp'),
    join_paths(libhatchet_network_dir, 'MsgProcessor.cpp'),
    join_paths(libhatchet_network_dir, 'StreamConnection.cpp'),
    join_paths(libhatchet_network_dir, 'DbSyncConnection.cpp'),
    join_paths(libhatchet_network_dir, 'RemoteCollection.cpp'),
    join_paths(libhatchet_network_dir, 'PortFwdThread.cpp'),
    join_paths(libhatchet_network_dir, 'Servent.cpp'),
    join_paths(libhatchet_network_dir, 'Connection.cpp'),
    join_paths(libhatchet_network_dir, 'ControlConnection.cpp'),
    join_paths(libhatchet_network_dir, 'QTcpSocketExtra.cpp'),
    join_paths(libhatchet_network_dir, 'ConnectionManager.cpp'))


libhatchet_moc_h += files(
    join_paths(libhatchet_network_dir, 'acl/AclRegistry.h'),
    join_paths(libhatchet_network_dir, 'acl/AclRequest.h'),
    join_paths(libhatchet_network_dir, 'BufferIoDevice.h'),
    join_paths(libhatchet_network_dir, 'Connection.h'),
    join_paths(libhatchet_network_dir, 'ConnectionManager.h'),
    join_paths(libhatchet_network_dir, 'ControlConnection.h'),
    join_paths(libhatchet_network_dir, 'DbSyncConnection.h'),
    join_paths(libhatchet_network_dir, 'MsgProcessor.h'),
    join_paths(libhatchet_network_dir, 'PortFwdThread.h'),
    join_paths(libhatchet_network_dir, 'QTcpSocketExtra.h'),
    join_paths(libhatchet_network_dir, 'RemoteCollection.h'),
    join_paths(libhatchet_network_dir, 'Servent.h'),
    join_paths(libhatchet_network_dir, 'Servent_p.h'),
    join_paths(libhatchet_network_dir, 'StreamConnection.h'))

