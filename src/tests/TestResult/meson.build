# TestResult build file
#========================================================================

test_result_inc = hatchet_inc
test_result_dir = meson.current_source_dir()


# dependancies
#========================================================================

test_result_dep_list = [
    qt5_dep,

    libhatchet_dep,
]


# src
#========================================================================


test_result_src = files(
    join_paths(test_result_dir, 'main.cpp'))

test_result_h = files(
    join_paths(test_result_dir, 'TestResult.h'))

# preprocess qt5
#---------------------------------------------------
test_result_src += qt5.preprocess(
    moc_sources : test_result_src,
    moc_headers : test_result_h,
    include_directories : test_result_inc,
    dependencies : test_result_dep_list)

# include directories
#========================================================================


# include current dir
#---------------------------------------------------
test_result_inc += include_directories('.')


# build
#========================================================================


# set build args
#---------------------------------------------------
test_result_link_args = []

test_result_cxx_args = []


# build library
#---------------------------------------------------
test_result_bin = executable(
    'hatchet-test-result',
    sources : [
        test_result_src],
    install : false,
    include_directories : test_result_inc,
    cpp_args : test_result_cxx_args,
    link_args : test_result_link_args,
    dependencies : test_result_dep_list,
    gnu_symbol_visibility: 'hidden')


# test
#========================================================================

