# libtomahawk/resolvers build file
#============================================================================


libtomahawk_inc += include_directories('.')
libtomahawk_resolvers_dir = meson.current_source_dir()


libtomahawk_src += files(
    join_paths(libtomahawk_resolvers_dir, 'ExternalResolver.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'Resolver.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptCommand_AllArtists.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptCommand_AllAlbums.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptCommand_AllTracks.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptCommand_LookupUrl.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptCommandQueue.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptPluginFactory.cpp'),
    
    # ScriptPlugins
    join_paths(libtomahawk_resolvers_dir, 'ScriptCollection.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'plugins/ScriptCollectionFactory.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptInfoPlugin.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'plugins/ScriptInfoPluginFactory.cpp'))



libtomahawk_gui_src += files(
    join_paths(libtomahawk_resolvers_dir, 'ExternalResolverGui.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptResolver.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'JSResolver.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'JSResolverHelper.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptEngine.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'JSAccount.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptJob.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'SyncScriptJob.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptObject.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptLinkGeneratorPlugin.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptAccount.cpp'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptPlugin.cpp'))


libtomahawk_moc_h += files(
    join_paths(libtomahawk_resolvers_dir, 'ExternalResolverGui.h'),
    join_paths(libtomahawk_resolvers_dir, 'ExternalResolver.h'),
    join_paths(libtomahawk_resolvers_dir, 'JSAccount.h'),
    join_paths(libtomahawk_resolvers_dir, 'JSResolver.h'),
    join_paths(libtomahawk_resolvers_dir, 'JSResolverHelper.h'),
    join_paths(libtomahawk_resolvers_dir, 'Resolver.h'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptAccount.h'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptCollection.h'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptCommand_AllAlbums.h'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptCommand_AllArtists.h'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptCommand_AllTracks.h'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptCommand_LookupUrl.h'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptCommandQueue.h'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptEngine.h'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptInfoPlugin.h'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptJob.h'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptLinkGeneratorPlugin.h'),
    join_paths(libtomahawk_resolvers_dir, 'ScriptResolver.h'),
    join_paths(libtomahawk_resolvers_dir, 'SyncScriptJob.h'))
