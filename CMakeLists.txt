cmake_minimum_required(VERSION 3.0.0)

project(fslp)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(fcppt REQUIRED)
find_package(Metal REQUIRED)

include(FcpptCMakeUtils)

fcppt_utils_static_shared()

add_library(fslp_interface INTERFACE)

target_include_directories(
	fslp_interface
	INTERFACE
	include
)

set(
	FSLP_FILES
	include/fslp/apply.hpp
	include/fslp/compose.hpp
	include/fslp/detail/make_fix.hpp
	include/fslp/fix.hpp
	include/fslp/fix_fwd.hpp
	include/fslp/forest.hpp
	include/fslp/forest_alg.hpp
	include/fslp/forest_alg_eval.hpp
	include/fslp/forest_alg_fix.hpp
	include/fslp/forest_alg_t.hpp
	include/fslp/forest_alg_x.hpp
	include/fslp/forest_alg_x_fix.hpp
	include/fslp/forest_alg_x_t.hpp
	include/fslp/forest_fix.hpp
	include/fslp/forest_t.hpp
	include/fslp/forest_x.hpp
	include/fslp/forest_x_fix.hpp
	include/fslp/forest_x_r.hpp
	include/fslp/slp.hpp
	include/fslp/tree.hpp
	include/fslp/tree_fix.hpp
	include/fslp/tree_x.hpp
	include/fslp/tree_x_fix.hpp
	include/fslp/unfold.hpp
	include/fslp/var.hpp
	src/nav.cpp
	src/old.cpp
)

option(ENABLE_TEST "Build the tests" ON)

if(ENABLE_TEST)
	find_package(Catch2 REQUIRED)
	fcppt_utils_setup_tests()
	enable_testing()
	add_subdirectory(test)
endif()
