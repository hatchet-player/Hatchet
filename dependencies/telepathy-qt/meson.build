# Telepathy-QT Dependency File
#============================================================================


# Look for telepathy-qt, a required dependency.
#---------------------------------------------------
telepathy_dep = dependency(
    'TelepathyQt5',
    version : '>= 0.9.8')


# Set HAVE_TELEPATHY in config.h
#---------------------------------------------------  
config_h.set(
    'HAVE_TELEPATHY',
    telepathy_dep.found(),
    description : 
        'Telepathy-Qt is needed for sharing Jabber/GTalk accounts ' +
        'with Telepathy.')
