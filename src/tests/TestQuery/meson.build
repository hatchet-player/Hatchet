# TestQuery build file
#========================================================================

test_query_inc = hatchet_inc
test_query_dir = meson.current_source_dir()


# dependancies
#========================================================================

test_query_dep_list = [
    qt5_dep,

    libhatchet_dep,
]


# src
#========================================================================


test_query_src = files(
    join_paths(test_query_dir, 'main.cpp'))

test_query_h = files(
    join_paths(test_query_dir, 'TestQuery.h'))

# preprocess qt5
#---------------------------------------------------
test_query_src += qt5.preprocess(
    moc_sources : test_query_src,
    moc_headers : test_query_h,
    include_directories : test_query_inc,
    dependencies : test_query_dep_list)

# include directories
#========================================================================


# include current dir
#---------------------------------------------------
test_query_inc += include_directories('.')


# build
#========================================================================


# set build args
#---------------------------------------------------
test_query_link_args = []

test_query_cxx_args = []


# build library
#---------------------------------------------------
test_query_bin = executable(
    'hatchet-test-query',
    sources : [
        test_query_src],
    install : false,
    include_directories : test_query_inc,
    cpp_args : test_query_cxx_args,
    link_args : test_query_link_args,
    dependencies : test_query_dep_list,
    gnu_symbol_visibility: 'hidden')


# test
#========================================================================

