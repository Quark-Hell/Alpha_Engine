set(engine_anomaly_list)
option(ANOMALY_ENGINE "Build graphics engine. Require WINDOWS_MANAGER option" ON)

if(ANOMALY_ENGINE AND NOT TARGET WINDOWS_MANAGER)
    message( FATAL_ERROR "For use ANOMALY_ENGINE you should turn on WINDOWS_MANAGER" )
endif ()

if (WINDOWS_MANAGER AND ANOMALY_ENGINE)
    set (ANOMALY_ENGINE_SOURCE "${CMAKE_CURRENT_LIST_DIR}")

    message("${Cyan}include .cpp engine_anomaly_list${ColourReset}")

    recurse_add_cpp_items(${ANOMALY_ENGINE_SOURCE}/AnomalyEngine engine_anomaly_list)
    recurse_copy_headers("${ANOMALY_ENGINE_SOURCE}/AnomalyEngine" "${BUILD_DIR}/headers/AnomalyEngine")
    recurse_copy_assets("${ANOMALY_ENGINE_SOURCE}/AnomalyEngine/Assets" "${BUILD_DIR}/Assets")

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

    add_library(ANOMALY_ENGINE STATIC ${engine_anomaly_list})
    add_dependencies(ANOMALY_ENGINE WINDOWS_MANAGER)

    if(LOGGER_INCLUDED)
        target_compile_definitions(ANOMALY_ENGINE PRIVATE LOGGER_INCLUDED)
    endif()

    target_link_libraries(ANOMALY_ENGINE
            PRIVATE WINDOWS_MANAGER
            PRIVATE glfw
    )

    target_include_directories(ANOMALY_ENGINE
        PUBLIC "${ANOMALY_ENGINE_SOURCE}"

        PRIVATE "${ANOMALY_ENGINE_SOURCE}/External"
        PRIVATE "${ANOMALY_ENGINE_SOURCE}/External/glad/include"
        PRIVATE "${Engine_Source}/Core"
        PRIVATE "${Engine_Source}/Core/External"
    )
endif ()