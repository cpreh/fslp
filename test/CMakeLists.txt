include(CMakeParseArguments)

function(add_fslp_test PATH_NAME)
	set(MULTI_ARGS LINK_LIBS)

	cmake_parse_arguments("" "" "" "${MULTI_ARGS}" ${ARGN} )

	fcppt_utils_add_test(
		${FCPPT_UTILS_PROJECT_SOURCE_DIR}/test
		"${PATH_NAME}"
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
add_fslp_test(forest_alg_x_eval)
add_fslp_test(forest_x)
add_fslp_test(map LINK_LIBS fcppt_catch_interface ${fcppt_core_TARGET})
add_fslp_test(slp)
add_fslp_test(unfold)
