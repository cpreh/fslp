cmake_minimum_required(VERSION 3.27.0)

project(fslp)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(fcppt REQUIRED)

set(FCPPT_UTILS_CLANG_TIDY_WHITELIST "fcppt" "fslp")

include(FcpptCMakeUtils)

fcppt_utils_static_shared()

add_library(fslp_interface INTERFACE)

target_include_directories(fslp_interface INTERFACE include)

fcppt_utils_load_source_files(files.txt FSLP_FILES)

fcppt_utils_add_source_groups("${FSLP_FILES}")

fcppt_utils_add_dummy_target(fslp "${FSLP_FILES}")
fcppt_utils_set_target_compiler_flags(fslp_dummy)
target_include_directories(fslp_dummy PRIVATE include)
target_link_libraries(fslp_dummy PRIVATE fcppt_core_interface fcppt_catch_interface)
set_target_properties(fslp_dummy PROPERTIES FOLDER fslp)

option(ENABLE_TEST "Build the tests" ON)

if(ENABLE_TEST)
  find_package(Catch2 REQUIRED)
  fcppt_utils_setup_tests()
  enable_testing()
  add_subdirectory(test)
endif()
