cmake_minimum_required(
	VERSION
	3.0.0
)

project(
	fslp
)

set_property(
	GLOBAL
	PROPERTY
	USE_FOLDERS
	ON
)

include(
	GNUInstallDirs
)

find_package(
	fcppt
	REQUIRED
)

find_package(
	Metal
	REQUIRED
)

include(
	FcpptCMakeUtils
)

set(
	FSLP_FILES
	src/main.cpp
)

add_executable(
	fslp
	${FSLP_FILES}
)

target_link_libraries(
	fslp
	fcppt_core_interface
)

fcppt_utils_set_target_compiler_flags(
	fslp
)
