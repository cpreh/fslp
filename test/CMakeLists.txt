function(add_fslp_test PATH_NAME)
	fcppt_utils_add_test(
		${FCPPT_UTILS_PROJECT_SOURCE_DIR}/test
		"${PATH_NAME}"
		LINK_LIBS
			fslp_interface
			fcppt_core_interface
	)
endfunction()

add_fslp_test(apply)
add_fslp_test(forest)
add_fslp_test(forest_alg)
add_fslp_test(forest_x)
