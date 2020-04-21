add_executable(
	test_engine
	DataStructures/test_SparseSet.cpp
	Utilities/test_vector_utils.cpp
	DataStructures/Iterators/test_random_access_iterator.cpp
)

target_link_libraries(
	test_engine
	PRIVATE project_warnings project_options sigma_engine gtest gmock gtest_main
)

add_test(NAME test_engine COMMAND test_engine)