# tomahawk.dialogs build file
#============================================================================

tomahawk_inc += include_directories('.')
tomahawk_dialogs_dir = meson.current_source_dir()


# Sources
#============================================================================


tomahawk_gui_src += files(
    join_paths(tomahawk_dialogs_dir, 'DiagnosticsDialog.cpp'),
    join_paths(tomahawk_dialogs_dir, 'LoadPlaylistDialog.cpp'),
    join_paths(tomahawk_dialogs_dir, 'SettingsDialog.cpp'))

tomahawk_moc_h += files(
    join_paths(tomahawk_dialogs_dir, 'DiagnosticsDialog.h'),
    join_paths(tomahawk_dialogs_dir, 'LoadPlaylistDialog.h'),
    join_paths(tomahawk_dialogs_dir, 'SettingsDialog.h'))

tomahawk_moc_ui += files(
    join_paths(tomahawk_dialogs_dir, 'DiagnosticsDialog.ui'),
    join_paths(tomahawk_dialogs_dir, 'HostDialog.ui'),
    join_paths(tomahawk_dialogs_dir, 'LoadPlaylistDialog.ui'),
    join_paths(tomahawk_dialogs_dir, 'ProxyDialog.ui'),
    join_paths(tomahawk_dialogs_dir, 'Settings_Accounts.ui'),
    join_paths(tomahawk_dialogs_dir, 'Settings_Advanced.ui'),
    join_paths(tomahawk_dialogs_dir, 'Settings_Collection.ui'),
    join_paths(tomahawk_dialogs_dir, 'Settings_Downloads.ui'))
