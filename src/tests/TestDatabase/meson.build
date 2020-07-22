# TestDatabase build file
#========================================================================

test_database_inc = hatchet_inc
test_database_dir = meson.current_source_dir()


# dependancies
#========================================================================

test_database_dep_list = [
    qt5_dep,

    libhatchet_dep,
]


# src
#========================================================================


test_database_src = files(
    join_paths(test_database_dir, 'main.cpp'))

test_database_h = files(
    join_paths(test_database_dir, 'TestDatabase.h'))

# preprocess qt5
#---------------------------------------------------
test_database_src += qt5.preprocess(
    moc_sources : test_database_src,
    moc_headers : test_database_h,
    include_directories : test_database_inc,
    dependencies : test_database_dep_list)

# include directories
#========================================================================


# include current dir
#---------------------------------------------------
test_database_inc += include_directories('.')


# build
#========================================================================


# set build args
#---------------------------------------------------
test_database_link_args = []

test_database_cxx_args = []


# build library
#---------------------------------------------------
test_database_bin = executable(
    'hatchet-test-database',
    sources : [
        test_database_src],
    install : false,
    include_directories : test_database_inc,
    cpp_args : test_database_cxx_args,
    link_args : test_database_link_args,
    dependencies : test_database_dep_list,
    gnu_symbol_visibility: 'hidden')


# test
#========================================================================

