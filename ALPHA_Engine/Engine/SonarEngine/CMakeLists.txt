set(engine_sonar_list)
option(AUDIO_SONAR_ENGINE "Build audio engine." ON)

if(AUDIO_SONAR_ENGINE)
    include(FetchContent)

    set(EXTERNAL_DIR "${Engine_Source}/SonarEngine/External")

    set(OpenAL_Install_Dir "${EXTERNAL_DIR}/OpenAL")
    set(DR_Install_Dir "${EXTERNAL_DIR}/Dr_Libs/")
    
    recurse_add_cpp_items("${Engine_Source}/SonarEngine" engine_sonar_list)
    recurse_copy_headers("${Engine_Source}/SonarEngine" "${Build_Dir}/headers/SonarEngine")
    
    set(OPENAL_INCLUDE_DIR "${OpenAL_Install_Dir}/include")
    if(WIN32)
        set(OPENAL_LIB "${OpenAL_Install_Dir}/lib/OpenAL32.lib")
    else()
        set(OPENAL_LIB "${OpenAL_Install_Dir}/lib/libOpenAL32.dll.a")
    endif()

    copy_file("${OpenAL_Install_Dir}/bin/OpenAL32.dll" "${Build_Dir}/external/OpenAL32.dll")

    include_directories(${OPENAL_INCLUDE_DIR})
    include_directories(${DR_Install_Dir})

    add_library(AUDIO_SONAR_ENGINE STATIC ${engine_sonar_list})
    
    target_include_directories(AUDIO_SONAR_ENGINE PRIVATE ${OPENAL_INCLUDE_DIR})
    target_link_libraries(AUDIO_SONAR_ENGINE PRIVATE ${OPENAL_LIB})
endif()
