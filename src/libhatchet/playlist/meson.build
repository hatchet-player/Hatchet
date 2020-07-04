# libtomahawk/playlist build file
#============================================================================

libtomahawk_inc += include_directories('.')
libtomahawk_playlist_dir = meson.current_source_dir()


libtomahawk_src += files(
    join_paths(libtomahawk_playlist_dir, 'PlaylistUpdaterInterface.cpp'),
    join_paths(libtomahawk_playlist_dir, 'PlaylistTemplate.cpp'),
    join_paths(libtomahawk_playlist_dir, 'XspfPlaylistTemplate.cpp'),
    join_paths(libtomahawk_playlist_dir, 'XspfUpdater.cpp'))

libtomahawk_gui_src += files(
    join_paths(libtomahawk_playlist_dir, 'InboxModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'InboxView.cpp'),
    join_paths(libtomahawk_playlist_dir, 'ContextView.cpp'),
    join_paths(libtomahawk_playlist_dir, 'TreeModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'TreeProxyModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'TreeProxyModelPlaylistInterface.cpp'),
    join_paths(libtomahawk_playlist_dir, 'ColumnItemDelegate.cpp'),
    join_paths(libtomahawk_playlist_dir, 'ColumnViewPreviewWidget.cpp'),
    join_paths(libtomahawk_playlist_dir, 'PlaylistModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'PlaylistItemDelegate.cpp'),
    join_paths(libtomahawk_playlist_dir, 'QueueProxyModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'QueueView.cpp'),
    join_paths(libtomahawk_playlist_dir, 'PlayableModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'PlayableProxyModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'PlayableProxyModelPlaylistInterface.cpp'),
    join_paths(libtomahawk_playlist_dir, 'TrackView.cpp'),
    join_paths(libtomahawk_playlist_dir, 'AlbumModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'GridItemDelegate.cpp'),
    join_paths(libtomahawk_playlist_dir, 'GridView.cpp'),
    join_paths(libtomahawk_playlist_dir, 'ColumnView.cpp'),
    join_paths(libtomahawk_playlist_dir, 'ViewHeader.cpp'),
    join_paths(libtomahawk_playlist_dir, 'LovedTracksModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'RecentlyLovedTracksModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'TopLovedTracksModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'RecentlyAddedModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'RecentlyPlayedModel.cpp'),
    join_paths(libtomahawk_playlist_dir, 'TrackItemDelegate.cpp'),
    join_paths(libtomahawk_playlist_dir, 'PlayableItem.cpp'),
    join_paths(libtomahawk_playlist_dir, 'SingleTrackPlaylistInterface.cpp'),
    join_paths(libtomahawk_playlist_dir, 'RevisionQueueItem.cpp'),
    join_paths(libtomahawk_playlist_dir, 'TrackDetailView.cpp'))


libtomahawk_moc_ui += files(
    join_paths(libtomahawk_playlist_dir, 'QueueView.ui'))


libtomahawk_moc_h += files(
    join_paths(libtomahawk_playlist_dir, 'AlbumModel.h'),
    join_paths(libtomahawk_playlist_dir, 'ColumnItemDelegate.h'),
    join_paths(libtomahawk_playlist_dir, 'ColumnView.h'),
    join_paths(libtomahawk_playlist_dir, 'ColumnViewPreviewWidget.h'),
    join_paths(libtomahawk_playlist_dir, 'ContextView.h'),
    join_paths(libtomahawk_playlist_dir, 'GridItemDelegate.h'),
    join_paths(libtomahawk_playlist_dir, 'GridView.h'),
    join_paths(libtomahawk_playlist_dir, 'InboxModel.h'),
    join_paths(libtomahawk_playlist_dir, 'InboxView.h'),
    join_paths(libtomahawk_playlist_dir, 'LovedTracksModel.h'),
    join_paths(libtomahawk_playlist_dir, 'PlayableItem.h'),
    join_paths(libtomahawk_playlist_dir, 'PlayableModel.h'),
    join_paths(libtomahawk_playlist_dir, 'PlayableProxyModel.h'),
    join_paths(libtomahawk_playlist_dir, 'PlayableProxyModelPlaylistInterface.h'),
    join_paths(libtomahawk_playlist_dir, 'PlaylistItemDelegate.h'),
    join_paths(libtomahawk_playlist_dir, 'PlaylistModel.h'),
    join_paths(libtomahawk_playlist_dir, 'PlaylistTemplate.h'),
    join_paths(libtomahawk_playlist_dir, 'PlaylistUpdaterInterface.h'),
    join_paths(libtomahawk_playlist_dir, 'QueueProxyModel.h'),
    join_paths(libtomahawk_playlist_dir, 'QueueView.h'),
    join_paths(libtomahawk_playlist_dir, 'RecentlyAddedModel.h'),
    join_paths(libtomahawk_playlist_dir, 'RecentlyLovedTracksModel.h'),
    join_paths(libtomahawk_playlist_dir, 'RecentlyPlayedModel.h'),
    join_paths(libtomahawk_playlist_dir, 'SingleTrackPlaylistInterface.h'),
    join_paths(libtomahawk_playlist_dir, 'TopLovedTracksModel.h'),
    join_paths(libtomahawk_playlist_dir, 'TrackDetailView.h'),
    join_paths(libtomahawk_playlist_dir, 'TrackItemDelegate.h'),
    join_paths(libtomahawk_playlist_dir, 'TrackView.h'),
    join_paths(libtomahawk_playlist_dir, 'TreeModel.h'),
    join_paths(libtomahawk_playlist_dir, 'TreeProxyModel.h'),
    join_paths(libtomahawk_playlist_dir, 'TreeProxyModelPlaylistInterface.h'),
    join_paths(libtomahawk_playlist_dir, 'ViewHeader.h'),
    join_paths(libtomahawk_playlist_dir, 'XspfPlaylistTemplate.h'),
    join_paths(libtomahawk_playlist_dir, 'XspfUpdater.h'))


libtomahawk_playlist_dirs = [
    'dynamic']


foreach dir : libtomahawk_playlist_dirs
    subdir(dir)
endforeach

    