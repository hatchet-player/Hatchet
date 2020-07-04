# libtomahawk/jobview build file
#============================================================================


libtomahawk_inc += include_directories('.')
libtomahawk_jobview_dir = meson.current_source_dir()

libtomahawk_src += files(
    join_paths(libtomahawk_jobview_dir, 'JobStatusItem.cpp'))


libtomahawk_gui_src += files(
    join_paths(libtomahawk_jobview_dir, 'JobStatusModel.cpp'),
    join_paths(libtomahawk_jobview_dir, 'JobStatusDelegate.cpp'),
    join_paths(libtomahawk_jobview_dir, 'JobStatusView.cpp'),    
    join_paths(libtomahawk_jobview_dir, 'AclJobItem.cpp'),
    join_paths(libtomahawk_jobview_dir, 'PipelineStatusItem.cpp'),
    join_paths(libtomahawk_jobview_dir, 'ScannerStatusItem.cpp'),
    join_paths(libtomahawk_jobview_dir, 'TransferStatusItem.cpp'),
    join_paths(libtomahawk_jobview_dir, 'LatchedStatusItem.cpp'),
    join_paths(libtomahawk_jobview_dir, 'ErrorStatusMessage.cpp'),
    join_paths(libtomahawk_jobview_dir, 'IndexingJobItem.cpp'),
    join_paths(libtomahawk_jobview_dir, 'InboxJobItem.cpp'),
    join_paths(libtomahawk_jobview_dir, 'ScriptErrorStatusMessage.cpp'))


libtomahawk_moc_h += files(
    join_paths(libtomahawk_jobview_dir, 'AclJobItem.h'),
    join_paths(libtomahawk_jobview_dir, 'ErrorStatusMessage.h'),
    join_paths(libtomahawk_jobview_dir, 'InboxJobItem.h'),
    join_paths(libtomahawk_jobview_dir, 'IndexingJobItem.h'),
    join_paths(libtomahawk_jobview_dir, 'JobStatusDelegate.h'),
    join_paths(libtomahawk_jobview_dir, 'JobStatusItem.h'),
    join_paths(libtomahawk_jobview_dir, 'JobStatusModel.h'),
    join_paths(libtomahawk_jobview_dir, 'JobStatusView.h'),
    join_paths(libtomahawk_jobview_dir, 'LatchedStatusItem.h'),
    join_paths(libtomahawk_jobview_dir, 'PipelineStatusItem.h'),
    join_paths(libtomahawk_jobview_dir, 'ScannerStatusItem.h'),
    join_paths(libtomahawk_jobview_dir, 'ScriptErrorStatusMessage.h'),
    join_paths(libtomahawk_jobview_dir, 'TransferStatusItem.h'))

