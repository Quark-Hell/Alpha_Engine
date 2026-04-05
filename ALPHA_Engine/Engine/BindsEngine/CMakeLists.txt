option(BINDS_ENGINE "Build input system. Require WINDOWS_MANAGER option" ON)
set(engine_binds_list)

if(BINDS_ENGINE AND NOT WINDOWS_MANAGER)
    message(FATAL_ERROR "For use BINDS_ENGINE you should turn on WINDOWS_MANAGER" )
endif ()

if (WINDOWS_MANAGER AND BINDS_ENGINE)
    set (BINDS_ENGINE_SOURCE "${CMAKE_CURRENT_LIST_DIR}")

    message("${Cyan}include .cpp engine_binds_list${ColourReset}")
    recurse_add_cpp_items("${BINDS_ENGINE_SOURCE}/BindsEngine" engine_binds_list)
    recurse_copy_headers("${BINDS_ENGINE_SOURCE}/BindsEngine" "${BUILD_DIR}/headers/BindsEngine")

    add_library(BINDS_ENGINE STATIC ${engine_binds_list})
    add_dependencies(BINDS_ENGINE WINDOWS_MANAGER)

    #===================Link GLFW===================#
    find_package(glfw3)

    if(glfw3_FOUND)
        target_link_libraries(BINDS_ENGINE PRIVATE glfw)
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

    if(LOGGER_INCLUDED)
        target_compile_definitions(BINDS_ENGINE PRIVATE LOGGER_INCLUDED)
    endif()

    target_link_libraries(BINDS_ENGINE
            PRIVATE WINDOWS_MANAGER
            PRIVATE glfw
    )

    target_include_directories(BINDS_ENGINE
        PUBLIC "${BINDS_ENGINE_SOURCE}"

        PRIVATE "${BINDS_ENGINE_SOURCE}/External"
        PRIVATE "${Engine_Source}/Core"
        PRIVATE "${Engine_Source}/Core/External"
    )
endif ()

