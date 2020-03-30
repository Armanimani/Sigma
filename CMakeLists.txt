# from here: https://github.com/lefticus/cpp_starter_project/blob/master/

cmake_minimum_required(VERSION 3.16)

project(sigma CXX)
include(cmake/StandardProjectSettings.cmake)

# Link to this 'Library' to set the C++ standard / compile time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# Link to this 'Library' to use the warnings
add_library(project_warnings INTERFACE)

# Standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# Sanitizer options if supported by the compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# Enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)

# External dependencies
add_subdirectory(external)

# Engine sources
add_subdirectory(Sigma)

# Testing 
option(ENABLE_TESTING "Enable test builds" ON)
if(ENABLE_TESTING)
	include(CTest)
	enable_testing()
	message(STATUS "Building tests")
endif()