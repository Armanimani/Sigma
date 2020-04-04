add_library(
	sigma_engine
	src/Application/Application.cpp
)

target_include_directories(sigma_engine INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include> 
)

target_link_libraries(
	sigma_engine
	INTERFACE project_warnings project_options DirectX_math
)

add_subdirectory(test)