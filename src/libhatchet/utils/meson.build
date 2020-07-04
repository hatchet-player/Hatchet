# libtomahawk.utils build file
#============================================================================

libtomahawk_inc += include_directories('.')
libtomahawk_utils_dir = meson.current_source_dir()

libtomahawk_src += files(
    join_paths(libtomahawk_utils_dir, 'BinaryExtractWorker.cpp'),
    join_paths(libtomahawk_utils_dir, 'Cloudstream.cpp'),
    join_paths(libtomahawk_utils_dir, 'Json.cpp'),
    join_paths(libtomahawk_utils_dir, 'TomahawkUtils.cpp'),
    join_paths(libtomahawk_utils_dir, 'Logger.cpp'),
    join_paths(libtomahawk_utils_dir, 'TomahawkCache.cpp'),
    join_paths(libtomahawk_utils_dir, 'WeakObjectHash.cpp'),
    join_paths(libtomahawk_utils_dir, 'WeakObjectList.cpp'),
    join_paths(libtomahawk_utils_dir, 'WebPopup.cpp'),
    join_paths(libtomahawk_utils_dir, 'PluginLoader.cpp'),
    join_paths(libtomahawk_utils_dir, 'GuiHelpers.cpp'),
    
    # currently needed by SipStatusMessage :/
    join_paths(libtomahawk_utils_dir, 'TomahawkUtilsGui.cpp'))

libtomahawk_gui_src += files(
    join_paths(libtomahawk_utils_dir, 'AnimatedSpinner.cpp'),
    join_paths(libtomahawk_utils_dir, 'BinaryInstallerHelper.cpp'),
    join_paths(libtomahawk_utils_dir, 'Closure.cpp'),
    join_paths(libtomahawk_utils_dir, 'DpiScaler.cpp'),
    join_paths(libtomahawk_utils_dir, 'DropJobNotifier.cpp'),
    join_paths(libtomahawk_utils_dir, 'ImageRegistry.cpp'),
    join_paths(libtomahawk_utils_dir, 'ItunesLoader.cpp'),
    join_paths(libtomahawk_utils_dir, 'ItunesParser.cpp'),
    join_paths(libtomahawk_utils_dir, 'JspfLoader.cpp'),
    join_paths(libtomahawk_utils_dir, 'LinkGenerator.cpp'),
    join_paths(libtomahawk_utils_dir, 'LinkGeneratorPlugin.cpp'),
    join_paths(libtomahawk_utils_dir, 'M3uLoader.cpp'),
    join_paths(libtomahawk_utils_dir, 'NetworkReply.cpp'),
    join_paths(libtomahawk_utils_dir, 'NetworkProxyFactory.cpp'),
    join_paths(libtomahawk_utils_dir, 'NetworkAccessManager.cpp'),
    join_paths(libtomahawk_utils_dir, 'PixmapDelegateFader.cpp'),
    join_paths(libtomahawk_utils_dir, 'ProxyStyle.cpp'),
    join_paths(libtomahawk_utils_dir, 'ResultUrlChecker.cpp'),
    join_paths(libtomahawk_utils_dir, 'SharedTimeLine.cpp'),
    join_paths(libtomahawk_utils_dir, 'ShortenedLinkParser.cpp'),
    join_paths(libtomahawk_utils_dir, 'ShortLinkHelper.cpp'),
    join_paths(libtomahawk_utils_dir, 'SpotifyParser.cpp'),
    join_paths(libtomahawk_utils_dir, 'SmartPointerList.h'),
    join_paths(libtomahawk_utils_dir, 'TomahawkStyle.cpp'),
    join_paths(libtomahawk_utils_dir, 'TomahawkUtilsGui.cpp'),
    join_paths(libtomahawk_utils_dir, 'TomaHkLinkGeneratorPlugin.cpp'),
    join_paths(libtomahawk_utils_dir, 'WidgetDragFilter.cpp'),
    join_paths(libtomahawk_utils_dir, 'XspfGenerator.cpp'),
    join_paths(libtomahawk_utils_dir, 'XspfLoader.cpp'))


libtomahawk_moc_src += files(    
    join_paths(libtomahawk_utils_dir, 'GuiHelpers.cpp'))


libtomahawk_moc_h += files(
    join_paths(libtomahawk_utils_dir, 'AnimatedSpinner.h'),
    join_paths(libtomahawk_utils_dir, 'BinaryExtractWorker.h'),
    join_paths(libtomahawk_utils_dir, 'BinaryInstallerHelper.h'),
    join_paths(libtomahawk_utils_dir, 'Closure.h'),
    join_paths(libtomahawk_utils_dir, 'Cloudstream.h'),
    join_paths(libtomahawk_utils_dir, 'DropJobNotifier.h'),
    join_paths(libtomahawk_utils_dir, 'GroovesharkParser.h'),
    join_paths(libtomahawk_utils_dir, 'ItunesLoader.h'),
    join_paths(libtomahawk_utils_dir, 'ItunesParser.h'),
    join_paths(libtomahawk_utils_dir, 'JspfLoader.h'),
    join_paths(libtomahawk_utils_dir, 'LinkGenerator.h'),
    join_paths(libtomahawk_utils_dir, 'M3uLoader.h'),
    join_paths(libtomahawk_utils_dir, 'NetworkReply.h'),
    join_paths(libtomahawk_utils_dir, 'PixmapDelegateFader.h'),
    join_paths(libtomahawk_utils_dir, 'ResultUrlChecker.h'),
    join_paths(libtomahawk_utils_dir, 'SharedTimeLine.h'),
    join_paths(libtomahawk_utils_dir, 'ShortenedLinkParser.h'),
    join_paths(libtomahawk_utils_dir, 'ShortLinkHelper.h'),
    join_paths(libtomahawk_utils_dir, 'SmartPointerList.h'),
    join_paths(libtomahawk_utils_dir, 'SpotifyParser.h'),
    join_paths(libtomahawk_utils_dir, 'TomahawkCache.h'),
    join_paths(libtomahawk_utils_dir, 'WeakObjectHash.h'),
    join_paths(libtomahawk_utils_dir, 'WeakObjectList.h'),
    join_paths(libtomahawk_utils_dir, 'WebPopup.h'),
    join_paths(libtomahawk_utils_dir, 'WidgetDragFilter.h'),
    join_paths(libtomahawk_utils_dir, 'XspfGenerator.h'),
    join_paths(libtomahawk_utils_dir, 'XspfLoader.h'))


if (qca2_dep.found())
libtomahawk_gui_src += files(
    join_paths(libtomahawk_utils_dir, 'GroovesharkParser.cpp'))
endif