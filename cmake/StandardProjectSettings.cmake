# Set a default build type if none is specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(
		STATUS "Setting the default build type to 'Release' as none was specified"
	)
	set(
		CMAKE_BUILD_TYPE Release
		CACHE STRING "Build type" FORCE
	)
	
	# Set the possible values of build type for cmake-gui
	set_property(
		CACHE CMAKE_BUILD_TYPE PROPERTY
		STRING "Debug" "Release"
	)
endif()

# Run time optimization
option(
	ENABLE_IPO
	"Enable iterprocedural optimization, aka line-time optimization (LTO)."
	OFF
)

if (ENABLE_IPO)
	include(CheckIPOSupported)
	check_ipo_supported(RESULT result OUTPUT output)
	if(result)
		set(CMAKE_INTERPROCEDURAL_OPTIMIZATION = True)
	else()
		message(SEND_ERROR "IPO is not supported: ${output}")
	endif()
endif()