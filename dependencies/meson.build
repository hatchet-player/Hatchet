# Hatchet dependencies build file
#============================================================================


# Required dependencies
#---------------------------------------------------
dependencies_dirs = [
    'boost',
    'zlib',
    'sparsehash', 
    'lucene++',
    'libvlc',
    'gnutls',
    'qt5',
    'attica',
    'qxt',
    'qca2',
    'qtkeychain',
    'quazip',
    'libportfwd',
    'qt-certificate-addon',
    'kdsingleapplicationguard',
    'telepathy-qt']

# optional dependencies
#---------------------------------------------------
optional_dirs = [
    'taglib',
    'liblastfm']

if (get_option('with_crashreporter'))
    message('[TODO]: implement crashreporter :)')
    # optional_dirs += 'libcrashreporter-qt'
endif


# OS Specific Dependencies
#---------------------------------------------------
os_dirs = []

if ( sys_name.contains('darwin') )
    os_dirs = [
        'SPMediaKeyTap']
endif


# build Dependencies
#---------------------------------------------------
foreach dir : dependencies_dirs
    subdir(dir)
endforeach

foreach dir : optional_dirs
    subdir(dir)
endforeach

foreach dir : os_dirs
    subdir(dir)
endforeach