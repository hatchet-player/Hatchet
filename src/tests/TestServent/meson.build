# TestServent build file
#========================================================================

test_servent_inc = hatchet_inc
test_servent_dir = meson.current_source_dir()


# dependancies
#========================================================================

test_servent_dep_list = [
    qt5_dep,

    libhatchet_dep,
]


# src
#========================================================================


test_servent_src = files(
    join_paths(test_servent_dir, 'main.cpp'))

test_servent_h = files(
    join_paths(test_servent_dir, 'TestServent.h'))

# preprocess qt5
#---------------------------------------------------
test_servent_src += qt5.preprocess(
    moc_sources : test_servent_src,
    moc_headers : test_servent_h,
    include_directories : test_servent_inc,
    dependencies : test_servent_dep_list)

# include directories
#========================================================================


# include current dir
#---------------------------------------------------
test_servent_inc += include_directories('.')


# build
#========================================================================


# set build args
#---------------------------------------------------
test_servent_link_args = []

test_servent_cxx_args = []


# build library
#---------------------------------------------------
test_servent_bin = executable(
    'hatchet-test-servent',
    sources : [
        test_servent_src],
    install : false,
    include_directories : test_servent_inc,
    cpp_args : test_servent_cxx_args,
    link_args : test_servent_link_args,
    dependencies : test_servent_dep_list,
    gnu_symbol_visibility: 'hidden')


# test
#========================================================================

