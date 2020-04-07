add_executable(
	sigma_editor
	src/Editor.cpp
)

set(CMAKE_PREFIX_PATH "C:\\Qt\\5.14.1\\msvc2017_64")
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

target_link_libraries(
	sigma_editor
	PRIVATE Qt5::Widgets Qt5::Core Qt5::Widgets
	INTERFACE project_warnings project_options sigma_engine
)

add_custom_command(TARGET sigma_editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:sigma_editor>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:sigma_editor>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:sigma_editor>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin> $<TARGET_FILE_DIR:sigma_editor>/platforms/$<TARGET_FILE_NAME:Qt5::QWindowsIntegrationPlugin>
)