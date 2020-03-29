function(enable_sanitizers project_name)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
        option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

        if(ENABLE_COVERAGE)
            target_compile_options(project_options INTERFACE --coverage -O0 -g)
            target_link_libraries(project_options INTERFACE --coverage)
        endif()

        set(SANITIZERS "")

        # Address sanitizer
        option(ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" FALSE)
        if(ENABLE_SANITIZER_ADDRESS)
            list(APPEND SANITIZERS "address")
        endif()

        # Memory sanitizer
        option(ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" FALSE)
        if(ENABLE_SANITIZER_MEMORY)
            list(APPEND SANITIZERS "memory")
        endif()

        # Undefined behavior sanitizer
        option(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "Enable undefined behavior sanitizer" FALSE)
        if(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR)
            list(APPEND SANITIZERS "undefined")
        endif()

        # Thread sanitizer 
        option(ENABLE_SANITIZER_THREAD "Enable thread sanitizer" FALSE)
        if(ENABLE_SANITIZER_THREAD)
            list(APPEND SANITIZERS "thread")
        endif()

        list(JOIN SANITIZERS "," LIST_OF_SANITIZERS)
        if(LIST_OF_SANITIZERS)
            if(NOT "${LIST_OF_SANITIZERS}" STREQUAL "")
                target_compile_options(${project_name} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
                target_link_libraries(${project_name} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
            endif()
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        # Address sanitizer
        option(ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" FALSE)
        if(ENABLE_SANITIZER_ADDRESS)
            target_compile_options(${project_name} INTERFACE -fsanitize=address)
            target_link_libraries(${project_name} INTERFACE -fsanitize=address)
        endif()    
    else()
        message(STATUS "There is no sanitizer support for this compiler")
    endif()
endfunction()