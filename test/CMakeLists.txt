include(CMakeParseArguments)

function(add_fslp_test PATH_NAME)
	set(OPTION_ARGS NO_CODE)
	set(MULTI_ARGS LINK_LIBS)

	cmake_parse_arguments("" "${OPTION_ARGS}" "" "${MULTI_ARGS}" ${ARGN} )

	if(_NO_CODE)
		set(NO_CODE NO_CODE)
	endif()

	fcppt_utils_add_test(
		${FCPPT_UTILS_PROJECT_SOURCE_DIR}/test
		"${PATH_NAME}"
		${NO_CODE}
		LINK_LIBS
			fslp_interface
			fcppt_core_interface
			${_LINK_LIBS}
	)
endfunction()

add_fslp_test(apply)
add_fslp_test(compose)
add_fslp_test(forest)
add_fslp_test(forest_alg)
add_fslp_test(forest_alg_eval)
add_fslp_test(forest_x)
add_fslp_test(map LINK_LIBS fcppt_catch_interface ${fcppt_core_TARGET})
#add_fslp_test(unfold)
#add_fslp_test(unfold_result NO_CODE)
