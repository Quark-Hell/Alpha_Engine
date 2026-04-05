set(CORE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" )

message("${Cyan}include .cpp engine_core_list${ColourReset}")

set(engine_core_list)
recurse_add_cpp_items("${CORE_PATH}/Core" engine_core_list)
recurse_copy_headers("${CORE_PATH}/Core" "${BUILD_DIR}/headers/Core")

add_library (
        ALPHA_ENGINE STATIC
        "${CORE_PATH}/Core/ALPHA_Engine.cpp"

        "${engine_core_list}"
)

option(LOGGER "Build logger" ON)
if(LOGGER)
    set(LOGGER_INCLUDED TRUE CACHE BOOL "" FORCE)
	target_compile_definitions(ALPHA_ENGINE PUBLIC LOGGER_INCLUDED)
	file(MAKE_DIRECTORY ${BUILD_DIR}/Logs)
endif()


#===================Link Assimp===================#
find_package(Assimp)

if(Assimp_FOUND)
    target_link_libraries(ALPHA_ENGINE PRIVATE assimp)
else()
    message(WARNING "Assimp not found, using manual linking")

    include(FetchContent)

    set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
    set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    
    FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v6.0.4
    )
    
    FetchContent_MakeAvailable(assimp)
    
    target_link_libraries(ALPHA_ENGINE
        PRIVATE assimp
    )
endif()
#===================Link Assimp===================#


target_compile_definitions(ALPHA_ENGINE
		PRIVATE _CRT_SECURE_NO_WARNINGS
)

target_include_directories(ALPHA_ENGINE PUBLIC ${CORE_PATH})
target_include_directories(ALPHA_ENGINE PUBLIC ${CORE_PATH}/External)

set_target_properties(ALPHA_ENGINE PROPERTIES PREFIX "")
set_target_properties(ALPHA_ENGINE PROPERTIES OUTPUT_NAME "ALPHA_ENGINE")