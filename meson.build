# Hatchet project build file
#============================================================================




# init
#============================================================================


# init project
#---------------------------------------------------
project(
    'hatchet',
    ['c', 'cpp'],
    default_options : [
        'cpp_std=c++11',
        'warning_level=3',
        # 'optimization=3',
        'debug=true'
    ],
    version : run_command(
        'python', '-c',
        '''with open('./VERSION','r') as f: print(f.read());''' ).stdout().strip(),
    license : 'GPLv3'
)

sys_name = host_machine.system().to_lower()

# init compiler 
#---------------------------------------------------
cpp = meson.get_compiler('cpp')

if sys_name.contains('darwin')
    objcpp = meson.get_compiler('objcpp')
endif

add_project_arguments(get_option('cxxflags'), language : 'cpp')
add_project_link_arguments(get_option('ldflags'), language: 'cpp')

qt5 = import('qt5')
cmake = import('cmake')
pkg = import('pkgconfig')
sys_name = host_machine.system().to_lower()


# init configuration
#---------------------------------------------------
config_h = configuration_data()

config_h.set(
    'HAVE_CXX17', 1,
    description : 'Define if the compiler supports basic C++17 syntax')

package_name = meson.project_name()
config_h.set_quoted(
    'PACKAGE_NAME', package_name,
    description : 'Define to the full name of this package.'
    )

package_tarname = meson.project_name()
config_h.set_quoted(
    'PACKAGE_TARNAME', package_tarname,
    description : 'Define to the one symbol short name of this package.')

package_version = meson.project_version()
config_h.set_quoted(
    'PACKAGE_VERSION', package_version,
    description : 'Define to the version of this package.')

package_string = '@0@ @1@'.format(package_name, package_version)
config_h.set_quoted(
    'PACKAGE_STRING', package_string,
    description : 'Define to the full name and version of this package.')

package_url = 'https://ever3st.com'
config_h.set_quoted(
    'PACKAGE_URL', package_url,
    description : 'Define to the home page for this package.')

package_bug_url = 'https://github.com/hatchet-player/Hatchet/issues'
config_h.set_quoted(
    'PACKAGE_BUGREPORT', package_bug_url,
    description : 'Define to the address where bug reports for this' +
    'package should be sent.')


# Hatchet application info
#---------------------------------------------------
hatchet_organization_name = 'hatchet'
hatchet_organization_domain = 'hatchet-player.org'
hatchet_application_name = 'Hatchet'
hatchet_description_summary = 'Hatchet media player'
hatchet_application_package_name = 'org.hatchet-player.Hatchet'




# env
#============================================================================


# set install directories
#---------------------------------------------------
prefix = get_option('prefix')
libdir = join_paths(prefix, get_option('libdir'))
bindir = join_paths(prefix, get_option('bindir'))
datadir = join_paths(prefix, get_option('datadir'))
sysconfdir = join_paths(prefix, get_option('sysconfdir'))
libexecdir = join_paths(prefix, get_option('libexecdir'))
mandir = join_paths(prefix, get_option('mandir'))
includedir = join_paths(prefix, get_option('includedir'))
hatchet_inc = [include_directories('.', 'src')]


# set cmake directories
#---------------------------------------------------
config_h.set_quoted('CMAKE_INSTALL_PREFIX', prefix)
config_h.set_quoted('CMAKE_INSTALL_LIBDIR', libdir)


# checking headers
#============================================================================




# checking functions
#============================================================================



# checking data types
#============================================================================




# Look For Required Programs
#============================================================================


# Git is 
# required for fetching subprojects & dependencies 
#----------------------------------------------------
git = find_program('git', required : true)


# Python is required for custom generators
#----------------------------------------------------
python = find_program('python', required : true)


# OS Specific checks 
#============================================================================


if (sys_name.contains('nt'))
    hatchet_target_name = 'hatchet'
    hatchet_system = 'Windows'
elif sys_name.contains('darwin')
    hatchet_target_name = 'hatchet'
    hatchet_system = 'OS X'
elif sys_name.contains('linux')
    hatchet_target_name = 'hatchet'
    hatchet_system = 'Linux'
else
    hatchet_target_name = 'Uknown Platform'
    hatchet_system = 'Please submit a ticket to resolve this issue' 
endif
hatchet_base_target_name = hatchet_target_name.to_lower()


# build
#============================================================================


# build hatchet
#---------------------------------------------------



project_dirs = [
    'dependencies',
    'extra',
    'src',
    #'admin'
    #'lang'
]


foreach dir : project_dirs
    subdir(dir)
endforeach


# foreach x : libhatchet_gui_src
#     a = run_command('echo', x).stdout().strip()
#     message(a)
# endforeach