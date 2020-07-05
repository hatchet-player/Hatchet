# libhatchet audio build file
#============================================================================

libhatchet_inc += include_directories('.')
libhatchet_audio_dir = meson.current_source_dir()


libhatchet_src += files(
    join_paths(libhatchet_audio_dir, 'AudioEngine.cpp'),
    join_paths(libhatchet_audio_dir, 'AudioOutput.cpp'),
    join_paths(libhatchet_audio_dir, 'MediaStream.cpp'),
    join_paths(libhatchet_audio_dir, 'Qnr_IoDeviceStream.cpp'))


libhatchet_moc_src += files(
    join_paths(libhatchet_audio_dir, 'AudioEngine.cpp'),
    join_paths(libhatchet_audio_dir, 'AudioOutput.cpp'),
    join_paths(libhatchet_audio_dir, 'MediaStream.cpp'),
    join_paths(libhatchet_audio_dir, 'Qnr_IoDeviceStream.cpp'))

libhatchet_moc_h += files(
    join_paths(libhatchet_audio_dir, 'AudioEngine.h'),
    join_paths(libhatchet_audio_dir, 'AudioOutput.h'),
    join_paths(libhatchet_audio_dir, 'MediaStream.h'),
    join_paths(libhatchet_audio_dir, 'AudioEngine_p.h'),
    join_paths(libhatchet_audio_dir, 'Qnr_IoDeviceStream.h'))
    
