cmake_minimum_required(VERSION 3.7.0)

project(fslp)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(fcppt REQUIRED)

set(
	FCPPT_UTILS_CLANG_TIDY_WHITELIST
	"fcppt"
	"fslp"
)

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
	include/fslp/base.hpp
	include/fslp/base_fwd.hpp
	include/fslp/clone.hpp
	include/fslp/compose.hpp
	include/fslp/detail/make_fix.hpp
	include/fslp/detail/make_slp.hpp
	include/fslp/detail/rotations.hpp
	include/fslp/fix.hpp
	include/fslp/fix_fwd.hpp
	include/fslp/fold.hpp
	include/fslp/forest.hpp
	include/fslp/forest_alg.hpp
	include/fslp/forest_alg_eval.hpp
	include/fslp/forest_alg_fix.hpp
	include/fslp/forest_alg_t.hpp
	include/fslp/forest_alg_x.hpp
	include/fslp/forest_alg_x_eval.hpp
	include/fslp/forest_alg_x_fix.hpp
	include/fslp/forest_alg_x_t.hpp
	include/fslp/forest_fix.hpp
	include/fslp/forest_t.hpp
	include/fslp/forest_x.hpp
	include/fslp/forest_x_fix.hpp
	include/fslp/forest_x_r.hpp
	include/fslp/make_nonempty.hpp
	include/fslp/map.hpp
	include/fslp/map_result.hpp
	include/fslp/nav/root.hpp
	include/fslp/nav/simple_string.hpp
	include/fslp/nav/simple_string_first.hpp
	include/fslp/nav/spine_alph.hpp
	include/fslp/nav/string.hpp
	include/fslp/nav/up.hpp
	include/fslp/nav/vert.hpp
	include/fslp/nonempty.hpp
	include/fslp/nonempty_fwd.hpp
	include/fslp/slp.hpp
	include/fslp/string_alg.hpp
	include/fslp/string_alg_eval.hpp
	include/fslp/string_alg_fix.hpp
	include/fslp/string_alg_t.hpp
	include/fslp/tree.hpp
	include/fslp/tree_fix.hpp
	include/fslp/tree_t.hpp
	include/fslp/tree_x.hpp
	include/fslp/tree_x_fix.hpp
	include/fslp/unfold.hpp
	include/fslp/var.hpp
)

fcppt_utils_add_source_groups("${FSLP_FILES}")

fcppt_utils_add_dummy_target(fslp "${FSLP_FILES}")
fcppt_utils_set_target_compiler_flags(fslp_dummy)
target_include_directories(fslp_dummy PRIVATE include)
target_link_libraries(fslp_dummy PRIVATE fcppt_core_interface)
set_target_properties(fslp_dummy PROPERTIES FOLDER fslp)

option(ENABLE_TEST "Build the tests" ON)

if(ENABLE_TEST)
	find_package(Catch2 REQUIRED)
	fcppt_utils_setup_tests()
	enable_testing()
	add_subdirectory(test)
endif()
