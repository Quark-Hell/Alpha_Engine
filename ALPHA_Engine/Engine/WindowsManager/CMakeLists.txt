option(WINDOWS_MANAGER "Build base render" ON)
set(engine_windows_manager_list)

if(WINDOWS_MANAGER)
    set (WINDOWS_MANAGER_SOURCE "${CMAKE_CURRENT_LIST_DIR}")

    message("${Cyan}include .cpp engine_windows_manager_list${ColourReset}")
    recurse_add_cpp_items("${WINDOWS_MANAGER_SOURCE}/WindowsManager" engine_windows_manager_list)
    recurse_copy_headers("${WINDOWS_MANAGER_SOURCE}/WindowsManager" "${BUILD_DIR}/headers/WindowsManager")

    #===================Link GLFW===================#
    find_package(glfw3)

    if(glfw3_FOUND)
        target_link_libraries(ALPHA_ENGINE PRIVATE glfw)
    else()
        message(WARNING "GLFW not found, using manual fetching and building")
    
        include(FetchContent)
    
        set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
        set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    
        FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG 3.3.9
        )
    
        FetchContent_MakeAvailable(glfw)
    endif()
    #===================/Link GLFW===================#

    add_library(
        WINDOWS_MANAGER STATIC 
        ${engine_windows_manager_list}

        ${WINDOWS_MANAGER_SOURCE}/External/glad/src/glad.c
    )

    target_link_libraries(WINDOWS_MANAGER
            PRIVATE glfw
    )

    if(LOGGER_INCLUDED)
        target_compile_definitions(WINDOWS_MANAGER PRIVATE LOGGER_INCLUDED)
    endif()

    target_include_directories(WINDOWS_MANAGER
        PUBLIC "${WINDOWS_MANAGER_SOURCE}"

        PRIVATE "${WINDOWS_MANAGER_SOURCE}/External/glad/include"
        PRIVATE "${Engine_Source}/Core"
        PRIVATE "${Engine_Source}/Core/External"
    )
endif()