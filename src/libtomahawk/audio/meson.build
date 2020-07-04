# libtomahawk audio build file
#============================================================================

libtomahawk_inc += include_directories('.')
libtomahawk_audio_dir = meson.current_source_dir()


libtomahawk_src += files(
    join_paths(libtomahawk_audio_dir, 'AudioEngine.cpp'),
    join_paths(libtomahawk_audio_dir, 'AudioOutput.cpp'),
    join_paths(libtomahawk_audio_dir, 'MediaStream.cpp'),
    join_paths(libtomahawk_audio_dir, 'Qnr_IoDeviceStream.cpp'))


libtomahawk_moc_src += files(
    join_paths(libtomahawk_audio_dir, 'AudioEngine.cpp'),
    join_paths(libtomahawk_audio_dir, 'AudioOutput.cpp'),
    join_paths(libtomahawk_audio_dir, 'MediaStream.cpp'),
    join_paths(libtomahawk_audio_dir, 'Qnr_IoDeviceStream.cpp'))

libtomahawk_moc_h += files(
    join_paths(libtomahawk_audio_dir, 'AudioEngine.h'),
    join_paths(libtomahawk_audio_dir, 'AudioOutput.h'),
    join_paths(libtomahawk_audio_dir, 'MediaStream.h'),
    join_paths(libtomahawk_audio_dir, 'AudioEngine_p.h'),
    join_paths(libtomahawk_audio_dir, 'Qnr_IoDeviceStream.h'))
    
