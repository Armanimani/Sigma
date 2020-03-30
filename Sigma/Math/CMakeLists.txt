add_library(sigma_math INTERFACE)

target_include_directories(sigma_math INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include> 
)

target_link_libraries(
	sigma_math
	INTERFACE project_warnings project_options
)

if(ENABLE_TESTING)
	add_subdirectory(test)
endif()