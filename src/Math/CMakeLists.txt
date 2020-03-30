add_library(sigma_math INTERFACE)

target_include_directories(sigma_math INTERFACE
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/Math>
	$<INSTALL_INTERFACE:include/Sigma:Math> 
)

target_link_libraries(
	sigma_math
	INTERFACE project_warnings project_options
)