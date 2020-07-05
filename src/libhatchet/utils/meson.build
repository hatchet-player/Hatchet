# libhatchet.utils build file
#============================================================================

libhatchet_inc += include_directories('.')
libhatchet_utils_dir = meson.current_source_dir()

libhatchet_src += files(
    join_paths(libhatchet_utils_dir, 'BinaryExtractWorker.cpp'),
    join_paths(libhatchet_utils_dir, 'Cloudstream.cpp'),
    join_paths(libhatchet_utils_dir, 'Json.cpp'),
    join_paths(libhatchet_utils_dir, 'HatchetUtils.cpp'),
    join_paths(libhatchet_utils_dir, 'Logger.cpp'),
    join_paths(libhatchet_utils_dir, 'HatchetCache.cpp'),
    join_paths(libhatchet_utils_dir, 'WeakObjectHash.cpp'),
    join_paths(libhatchet_utils_dir, 'WeakObjectList.cpp'),
    join_paths(libhatchet_utils_dir, 'WebPopup.cpp'),
    join_paths(libhatchet_utils_dir, 'PluginLoader.cpp'),
    join_paths(libhatchet_utils_dir, 'GuiHelpers.cpp'),
    
    # currently needed by SipStatusMessage :/
    join_paths(libhatchet_utils_dir, 'HatchetUtilsGui.cpp'))

libhatchet_gui_src += files(
    join_paths(libhatchet_utils_dir, 'AnimatedSpinner.cpp'),
    join_paths(libhatchet_utils_dir, 'BinaryInstallerHelper.cpp'),
    join_paths(libhatchet_utils_dir, 'Closure.cpp'),
    join_paths(libhatchet_utils_dir, 'DpiScaler.cpp'),
    join_paths(libhatchet_utils_dir, 'DropJobNotifier.cpp'),
    join_paths(libhatchet_utils_dir, 'ImageRegistry.cpp'),
    join_paths(libhatchet_utils_dir, 'ItunesLoader.cpp'),
    join_paths(libhatchet_utils_dir, 'ItunesParser.cpp'),
    join_paths(libhatchet_utils_dir, 'JspfLoader.cpp'),
    join_paths(libhatchet_utils_dir, 'LinkGenerator.cpp'),
    join_paths(libhatchet_utils_dir, 'LinkGeneratorPlugin.cpp'),
    join_paths(libhatchet_utils_dir, 'M3uLoader.cpp'),
    join_paths(libhatchet_utils_dir, 'NetworkReply.cpp'),
    join_paths(libhatchet_utils_dir, 'NetworkProxyFactory.cpp'),
    join_paths(libhatchet_utils_dir, 'NetworkAccessManager.cpp'),
    join_paths(libhatchet_utils_dir, 'PixmapDelegateFader.cpp'),
    join_paths(libhatchet_utils_dir, 'ProxyStyle.cpp'),
    join_paths(libhatchet_utils_dir, 'ResultUrlChecker.cpp'),
    join_paths(libhatchet_utils_dir, 'SharedTimeLine.cpp'),
    join_paths(libhatchet_utils_dir, 'ShortenedLinkParser.cpp'),
    join_paths(libhatchet_utils_dir, 'ShortLinkHelper.cpp'),
    join_paths(libhatchet_utils_dir, 'SpotifyParser.cpp'),
    join_paths(libhatchet_utils_dir, 'SmartPointerList.h'),
    join_paths(libhatchet_utils_dir, 'HatchetStyle.cpp'),
    join_paths(libhatchet_utils_dir, 'HatchetUtilsGui.cpp'),
    join_paths(libhatchet_utils_dir, 'HatchetLinkGeneratorPlugin.cpp'),
    join_paths(libhatchet_utils_dir, 'WidgetDragFilter.cpp'),
    join_paths(libhatchet_utils_dir, 'XspfGenerator.cpp'),
    join_paths(libhatchet_utils_dir, 'XspfLoader.cpp'))


libhatchet_moc_src += files(    
    join_paths(libhatchet_utils_dir, 'GuiHelpers.cpp'))


libhatchet_moc_h += files(
    join_paths(libhatchet_utils_dir, 'AnimatedSpinner.h'),
    join_paths(libhatchet_utils_dir, 'BinaryExtractWorker.h'),
    join_paths(libhatchet_utils_dir, 'BinaryInstallerHelper.h'),
    join_paths(libhatchet_utils_dir, 'Closure.h'),
    join_paths(libhatchet_utils_dir, 'Cloudstream.h'),
    join_paths(libhatchet_utils_dir, 'DropJobNotifier.h'),
    join_paths(libhatchet_utils_dir, 'GroovesharkParser.h'),
    join_paths(libhatchet_utils_dir, 'ItunesLoader.h'),
    join_paths(libhatchet_utils_dir, 'ItunesParser.h'),
    join_paths(libhatchet_utils_dir, 'JspfLoader.h'),
    join_paths(libhatchet_utils_dir, 'LinkGenerator.h'),
    join_paths(libhatchet_utils_dir, 'M3uLoader.h'),
    join_paths(libhatchet_utils_dir, 'NetworkReply.h'),
    join_paths(libhatchet_utils_dir, 'PixmapDelegateFader.h'),
    join_paths(libhatchet_utils_dir, 'ResultUrlChecker.h'),
    join_paths(libhatchet_utils_dir, 'SharedTimeLine.h'),
    join_paths(libhatchet_utils_dir, 'ShortenedLinkParser.h'),
    join_paths(libhatchet_utils_dir, 'ShortLinkHelper.h'),
    join_paths(libhatchet_utils_dir, 'SmartPointerList.h'),
    join_paths(libhatchet_utils_dir, 'SpotifyParser.h'),
    join_paths(libhatchet_utils_dir, 'HatchetCache.h'),
    join_paths(libhatchet_utils_dir, 'WeakObjectHash.h'),
    join_paths(libhatchet_utils_dir, 'WeakObjectList.h'),
    join_paths(libhatchet_utils_dir, 'WebPopup.h'),
    join_paths(libhatchet_utils_dir, 'WidgetDragFilter.h'),
    join_paths(libhatchet_utils_dir, 'XspfGenerator.h'),
    join_paths(libhatchet_utils_dir, 'XspfLoader.h'))


if (qca2_dep.found())
libhatchet_gui_src += files(
    join_paths(libhatchet_utils_dir, 'GroovesharkParser.cpp'))
endif