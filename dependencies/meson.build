# tomahawk dependencies build file
#============================================================================


# Required dependencies
#---------------------------------------------------
dependencies_dirs = [
    'boost',
    'zlib',
    'sparsehash', 
    'lucene++',
    'libportfwd',
    'libvlc',
    'gnutls',
    'qt5',
    'attica',
    'kdsingleapplicationguard',
    'qt-certificate-addon',
    'qxt',
    'qca2',
    'qtkeychain',
    'quazip',
    'telepathy-qt']

# optional dependencies
#---------------------------------------------------
optional_dirs = [
    'taglib',
    'echonest',
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