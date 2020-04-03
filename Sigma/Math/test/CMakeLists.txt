add_executable(
	test_math 
	"test_Vector.cpp"
	"test_Vector_utils.cpp"
	"test_Matrix.cpp"
)

target_link_libraries(
	test_math
	PRIVATE sigma_math project_warnings project_options gtest gmock gtest_main
)

add_test(NAME test_math COMMAND test_math)