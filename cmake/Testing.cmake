macro(package_add_test TESTNAME)
	add_executable(${TESTNAME} ${ARGN})
	target_link_libraries(
		${TESTNAME} 
		PRIVATE project_warnings project_options gtest gmock gtest_main
	)
	add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
endmacro()