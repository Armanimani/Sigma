add_library(DirectX_math INTERFACE)

target_include_directories(DirectX_math INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/DirectXMath/inc>
	$<INSTALL_INTERFACE:DirectXMath/inc> 
)

target_link_libraries(
	DirectX_math
	INTERFACE project_warnings project_options
)
