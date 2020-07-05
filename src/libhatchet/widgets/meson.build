# libhatchet.widgets build file
#============================================================================


libhatchet_inc += include_directories('.')
libhatchet_widgets_dir = meson.current_source_dir()

libhatchet_gui_src += files(
    join_paths(libhatchet_widgets_dir, 'AnimatedSplitter.cpp'),
    join_paths(libhatchet_widgets_dir, 'BasicHeader.cpp'),
    join_paths(libhatchet_widgets_dir, 'HoverControls.cpp'),
    join_paths(libhatchet_widgets_dir, 'BackgroundWidget.cpp'),
    join_paths(libhatchet_widgets_dir, 'Breadcrumb.cpp'),
    join_paths(libhatchet_widgets_dir, 'BreadcrumbButton.cpp'),
    join_paths(libhatchet_widgets_dir, 'ChartDataLoader.cpp'),
    join_paths(libhatchet_widgets_dir, 'ClickableLabel.cpp'),
    join_paths(libhatchet_widgets_dir, 'ComboBox.cpp'),
    join_paths(libhatchet_widgets_dir, 'DropDownButton.cpp'),
    join_paths(libhatchet_widgets_dir, 'DownloadButton.cpp'),
    join_paths(libhatchet_widgets_dir, 'ElidedLabel.cpp'),
    join_paths(libhatchet_widgets_dir, 'FilterHeader.cpp'),
    join_paths(libhatchet_widgets_dir, 'CaptionLabel.cpp'),
    join_paths(libhatchet_widgets_dir, 'HeaderLabel.cpp'),
    join_paths(libhatchet_widgets_dir, 'HistoryWidget.cpp'),
    join_paths(libhatchet_widgets_dir, 'ImageButton.cpp'),
    join_paths(libhatchet_widgets_dir, 'OverlayButton.cpp'),
    join_paths(libhatchet_widgets_dir, 'OverlayWidget.cpp'),
    join_paths(libhatchet_widgets_dir, 'PlayableCover.cpp'),
    join_paths(libhatchet_widgets_dir, 'PlaylistsModel.cpp'),
    join_paths(libhatchet_widgets_dir, 'QueryLabel.cpp'),
    join_paths(libhatchet_widgets_dir, 'RecentPlaylistsModel.cpp'),
    join_paths(libhatchet_widgets_dir, 'RecentlyPlayedPlaylistsModel.cpp'),
    join_paths(libhatchet_widgets_dir, 'ScriptCollectionHeader.cpp'),
    join_paths(libhatchet_widgets_dir, 'ScrollingLabel.cpp'),
    join_paths(libhatchet_widgets_dir, 'SeekSlider.cpp'),
    join_paths(libhatchet_widgets_dir, 'SourceTreePopupDialog.cpp'),
    join_paths(libhatchet_widgets_dir, 'ToggleButton.cpp'))


libhatchet_moc_ui += files(
    join_paths(libhatchet_widgets_dir, 'HeaderWidget.ui'))


libhatchet_moc_h += files(
    join_paths(libhatchet_widgets_dir, 'AnimatedSplitter.h'),
    join_paths(libhatchet_widgets_dir, 'BackgroundWidget.h'),
    join_paths(libhatchet_widgets_dir, 'BasicHeader.h'),
    join_paths(libhatchet_widgets_dir, 'BreadcrumbButton.h'),
    join_paths(libhatchet_widgets_dir, 'Breadcrumb.h'),
    join_paths(libhatchet_widgets_dir, 'CaptionLabel.h'),
    join_paths(libhatchet_widgets_dir, 'ChartDataLoader.h'),
    join_paths(libhatchet_widgets_dir, 'ClickableLabel.h'),
    join_paths(libhatchet_widgets_dir, 'ComboBox.h'),
    join_paths(libhatchet_widgets_dir, 'DownloadButton.h'),
    join_paths(libhatchet_widgets_dir, 'DropDownButton.h'),
    join_paths(libhatchet_widgets_dir, 'ElidedLabel.h'),
    join_paths(libhatchet_widgets_dir, 'FilterHeader.h'),
    join_paths(libhatchet_widgets_dir, 'HeaderLabel.h'),
    join_paths(libhatchet_widgets_dir, 'HistoryWidget.h'),
    join_paths(libhatchet_widgets_dir, 'HoverControls.h'),
    join_paths(libhatchet_widgets_dir, 'ImageButton.h'),
    join_paths(libhatchet_widgets_dir, 'OverlayButton.h'),
    join_paths(libhatchet_widgets_dir, 'OverlayWidget.h'),
    join_paths(libhatchet_widgets_dir, 'PlayableCover.h'),
    join_paths(libhatchet_widgets_dir, 'PlaylistsModel.h'),
    join_paths(libhatchet_widgets_dir, 'QueryLabel.h'),
    join_paths(libhatchet_widgets_dir, 'RecentlyPlayedPlaylistsModel.h'),
    join_paths(libhatchet_widgets_dir, 'RecentPlaylistsModel.h'),
    join_paths(libhatchet_widgets_dir, 'ScriptCollectionHeader.h'),
    join_paths(libhatchet_widgets_dir, 'ScrollingLabel.h'),
    join_paths(libhatchet_widgets_dir, 'SeekSlider.h'),
    join_paths(libhatchet_widgets_dir, 'SourceTreePopupDialog.h'),
    join_paths(libhatchet_widgets_dir, 'ToggleButton.h'))


libhatchet_widgets_dirs = [
    'searchlineedit']


foreach dir : libhatchet_widgets_dirs
    subdir(dir)
endforeach