set(engine_sonar_list)
option(AUDIO_SONAR_ENGINE "Build audio engine." ON)

if(AUDIO_SONAR_ENGINE)
    set(EXTERNAL_DIR "${Engine_Source}/SonarEngine/External")

    set(OpenAL_Source_Dir "${EXTERNAL_DIR}/OpenAL_Source/")
    set(OpenAL_Binary_Dir "${EXTERNAL_DIR}/OpenAL_Binary/")
    set(OpenAL_Install_Dir "${EXTERNAL_DIR}/OpenAL/")

    #Download function
    function(DownloadOpenAL)
        set(FETCHCONTENT_BASE_DIR "${OpenAL_Source_Dir}" CACHE PATH "" FORCE)

        FetchContent_Declare(
            openal_soft
            GIT_REPOSITORY https://github.com/kcat/openal-soft.git
            GIT_TAG master
            BINARY_DIR "${OpenAL_Binary_Dir}"
        )

        set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)
        set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
        set(ALSOFT_INSTALL ON CACHE BOOL "" FORCE)
        set(ALSOFT_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
        set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "" FORCE)

        set(CMAKE_INSTALL_PREFIX "${OpenAL_Install_Dir}" CACHE PATH "" FORCE)

        FetchContent_MakeAvailable(openal_soft)

        add_custom_target(OpenAL_Install ALL
            COMMAND ${CMAKE_COMMAND} --install ${OpenAL_Binary_Dir}
            COMMENT "Installing OpenAL to ${OpenAL_Install_Dir}"
        )
    endfunction()

    include(FetchContent)

    DownloadOpenAL()
    
    recurse_add_cpp_items("${Engine_Source}/SonarEngine" engine_sonar_list)
    recurse_copy_headers("${Engine_Source}/SonarEngine" "${Build_Dir}/headers/SonarEngine")
    
    set(OPENAL_INCLUDE_DIR "${OpenAL_Install_Dir}/include")
    if(WIN32)
        set(OPENAL_LIB "${OpenAL_Install_Dir}/lib/OpenAL32.lib")
    else()
        set(OPENAL_LIB "${OpenAL_Install_Dir}/lib/libopenal.a")
    endif()

    include_directories(${OPENAL_INCLUDE_DIR})

    add_library(AUDIO_SONAR_ENGINE STATIC ${engine_sonar_list})
    
    target_include_directories(AUDIO_SONAR_ENGINE PRIVATE ${OPENAL_INCLUDE_DIR})
    target_link_libraries(AUDIO_SONAR_ENGINE PRIVATE ${OPENAL_LIB})
endif()
