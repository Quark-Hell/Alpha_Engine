set(engine_sonar_list)
option(SONAR_ENGINE "Build audio engine." ON)

if(SONAR_ENGINE)
    set (SONAR_ENGINE_SOURCE "${CMAKE_CURRENT_LIST_DIR}")
    
    recurse_add_cpp_items("${SONAR_ENGINE_SOURCE}/SonarEngine" engine_sonar_list)
    recurse_copy_headers("${SONAR_ENGINE_SOURCE}/SonarEngine" "${BUILD_DIR}/headers/SonarEngine")

    add_library(SONAR_ENGINE STATIC ${engine_sonar_list})

    #===================Link OpenAL===================#
    find_package(OpenAL)
    
    if(OpenAL_FOUND)
        target_link_libraries(SONAR_ENGINE PRIVATE OpenAL::OpenAL)
    else()
        message(WARNING "OpenAL not found, using manual fetching and building")
    
        include(FetchContent)
    
        set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)
        set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
        set(ALSOFT_NO_CONFIG_UTIL ON CACHE BOOL "" FORCE)
        set(ALSOFT_INSTALL OFF CACHE BOOL "" FORCE)
        set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
        set(ALSOFT_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
        set(LIBTYPE "STATIC" CACHE STRING "" FORCE)
    
        FetchContent_Declare(
            openal
            GIT_REPOSITORY https://github.com/kcat/openal-soft.git
            GIT_TAG 1.24.2
        )
    
        FetchContent_MakeAvailable(openal)
    
        target_link_libraries(SONAR_ENGINE PRIVATE OpenAL)
    endif()
    #===================/Link OpenAL===================#

    if(LOGGER_INCLUDED)
        target_compile_definitions(SONAR_ENGINE PRIVATE LOGGER_INCLUDED)
    endif()
    
    target_include_directories(SONAR_ENGINE
        PUBLIC "${SONAR_ENGINE_SOURCE}"

        PRIVATE "${Engine_Source}/Core"
        PRIVATE "${Engine_Source}/Core/External"
    )
endif()
