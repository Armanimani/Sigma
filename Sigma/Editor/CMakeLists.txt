find_package(Qt5Widgets REQUIRED)

# TODO: Qt does not yet fully sipport buiilding with C++20
target_compile_features(Qt5::Widgets INTERFACE cxx_std_17)
target_compile_features(Qt5::Core INTERFACE cxx_std_17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(
	sigma_editor
	"src/main.cpp"
	"src/Editor/Editor.cpp")


target_link_libraries(
	sigma_editor
	INTERFACE project_options project_warnings sigma_engine
	PRIVATE Qt5::Widgets Qt5::Core 
)

target_include_directories(
	sigma_editor
	PRIVATE 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

add_custom_command(TARGET sigma_editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:sigma_editor>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:sigma_editor>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:sigma_editor>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin> $<TARGET_FILE_DIR:sigma_editor>/platforms/$<TARGET_FILE_NAME:Qt5::QWindowsIntegrationPlugin>
)