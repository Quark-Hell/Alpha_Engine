set(engine_axis_list)
option(PHYSICS_AXIS_ENGINE "Build physics engine." ON)

option(BUILD_PhysX "Build NVIDIA PhysX SDK." ON)
option(BUILD_PhysX_GPU_SUPPORT "Build NVIDIA PhysX SDK with CUDA toolkit." OFF)

#define build type
if(PHYSICS_AXIS_ENGINE)
    if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        set(BUILD_TYPE release)
    else()
        set(BUILD_TYPE debug)
    endif()
endif()

if(PHYSICS_AXIS_ENGINE)
    set(EXTERNAL_DIR "${Engine_Source}/AxisEngine/External")
    set(PHYSX_ROOT_DIR "${EXTERNAL_DIR}/PhysX-omni/physx")
    set(PHYSX_ROOT_INCLUDES_DIR "${PHYSX_ROOT_DIR}/include")
    set(PHYSX_ROOT_LIBS_DIR "${PHYSX_ROOT_DIR}/bin/win.x86_64.vc143.mt/${BUILD_TYPE}")

    set(PHYSX_INCLUDES_DIR "${Engine_Source}/AxisEngine/External/PhysX/include/PhysX")
    set(PHYSX_LIBS_DIR "${Engine_Source}/AxisEngine/External/PhysX/lib")

    set(PHYSX_LIBS)
endif()

function(setup_physx_includes physx_root_includes_dir physx_includes_dir result_var)
    file(GLOB physx_dir_contents "${physx_includes_dir}/*")
    
    if(physx_dir_contents)
        set(${result_var} TRUE PARENT_SCOPE)
    else()
        message(STATUS "PhysX includes not found in target directory, checking source...")
        
        file(GLOB physx_root_contents "${physx_root_includes_dir}/*")
        
        if(physx_root_contents)            
            recurse_copy_assets("${physx_root_includes_dir}" "${physx_includes_dir}")
            
            file(GLOB physx_dir_contents_after "${physx_includes_dir}/*")
            
            if(physx_dir_contents_after)
                set(${result_var} TRUE PARENT_SCOPE)
            else()
                set(${result_var} FALSE PARENT_SCOPE)
            endif()
        else()
            set(${result_var} FALSE PARENT_SCOPE)
        endif()
    endif()
endfunction()

function(setup_physx_libs physx_root_libs_dir physx_libs_dir result_var libs_var)
    if(WIN32)
        set(lib_prefix "")
        set(lib_extension ".lib")
    else()
        set(lib_prefix "lib")
        set(lib_extension ".a")
    endif()
    
    set(physx_lib_names
        PhysX
        PhysXCommon
        PhysXCooking
        PhysXExtensions
        PhysXFoundation
    )

    set(physx_libs_list
        "${physx_libs_dir}/${lib_prefix}PhysXFoundation_static_64${lib_extension}"
        "${physx_libs_dir}/${lib_prefix}PhysXCommon_static_64${lib_extension}"
        "${physx_libs_dir}/${lib_prefix}PhysXCooking_static_64${lib_extension}"
        "${physx_libs_dir}/${lib_prefix}PhysXExtensions_static_64${lib_extension}"
        "${physx_libs_dir}/${lib_prefix}PhysXPvdSDK_static_64${lib_extension}"
        "${physx_libs_dir}/${lib_prefix}PhysX_static_64${lib_extension}"
    )
        
    set(MISSING_LIBS "")
    foreach(LIB ${PHYSX_LIBS})
        if(NOT EXISTS "${LIB}")
            list(APPEND MISSING_LIBS "${LIB}")
        endif()
    endforeach()

    if(MISSING_LIBS)
        file(GLOB PHYSX_DIR_CONTENTS "${physx_root_libs_dir}/*")

        if(PHYSX_DIR_CONTENTS)
            recurse_copy_assets("${physx_root_libs_dir}" "${physx_libs_dir}")  
        endif()
    endif()

    #check that all libs are found
    set(MISSING_LIBS "")
    foreach(LIB ${PHYSX_LIBS})
        if(NOT EXISTS "${LIB}")
            list(APPEND MISSING_LIBS "${LIB}")
        endif()
    endforeach()

    if(MISSING_LIBS)
        set(FOUND_PHYSX_LIBS FALSE)
        set(${result_var} FALSE PARENT_SCOPE)
        set(${libs_var} "" PARENT_SCOPE)
    else()
        set(FOUND_PHYSX_LIBS TRUE)
        set(${result_var} TRUE PARENT_SCOPE)
        set(${libs_var} "${physx_libs_list}" PARENT_SCOPE)
    endif()
endfunction()

if(PHYSICS_AXIS_ENGINE)
    #find includes  
    setup_physx_includes(
        "${PHYSX_ROOT_INCLUDES_DIR}" 
        "${PHYSX_INCLUDES_DIR}" 
        FOUND_PHYSX_INCLUDES
    )

    #find libs
    setup_physx_libs(
        "${PHYSX_ROOT_LIBS_DIR}"
        "${PHYSX_LIBS_DIR}"
        FOUND_PHYSX_LIBS
        PHYSX_LIBS
    )
endif()

if(NOT FOUND_PHYSX_INCLUDES OR NOT FOUND_PHYSX_LIBS)
    set(PHYSX_DOWNLOADED FALSE)

    include(FetchContent)

    FetchContent_Declare(
        PhysXSDK
        GIT_REPOSITORY https://github.com/NVIDIA-Omniverse/PhysX.git
        GIT_TAG        main        
        SOURCE_DIR     "${EXTERNAL_DIR}/PhysX-omni"
    )
    
    FetchContent_MakeAvailable(PhysXSDK)
    set(PHYSX_DOWNLOADED TRUE)
endif()

#build PhysX
if (PHYSICS_AXIS_ENGINE AND BUILD_PhysX AND PHYSX_DOWNLOADED)
    set(BUILD_FOLDER "win.x86_64.vc143.mt")

	if(MSVC)
        if(MSVC_VERSION GREATER_EQUAL 1930)
            set(PHYSX_COMPILER "vc17")
        elseif(MSVC_VERSION GREATER_EQUAL 1920)
            set(PHYSX_COMPILER "vc16")
        else()
            set(PHYSX_COMPILER "vc15")
        endif()
    endif()

    if(BUILD_PhysX_GPU_SUPPORT)
        set(GPU_SUPPORT "")
    else()
        set(GPU_SUPPORT "-cpu-only")
    endif()

    set(PHYSX_PRESET "${PHYSX_COMPILER}win64${GPU_SUPPORT}")
    set(CONFIG_DIRECTORY "${PHYSX_COMPILER}win64${GPU_SUPPORT}")

    set(PRESET_FILE "${PHYSX_ROOT_DIR}/buildtools/presets/public/${PHYSX_PRESET}.xml")

    if(EXISTS ${PRESET_FILE})
        file(READ ${PRESET_FILE} PRESET_CONTENT)
        
        string(REGEX REPLACE 
                "PX_GENERATE_STATIC_LIBRARIES\" value=\"False\""
                "PX_GENERATE_STATIC_LIBRARIES\" value=\"True\""
                PRESET_CONTENT 
                "${PRESET_CONTENT}"
            )
        
        file(WRITE ${PRESET_FILE} "${PRESET_CONTENT}")
        message(STATUS "Patched preset for static libraries")
    endif()

	execute_process(
            COMMAND cmd /c generate_projects.bat ${PHYSX_PRESET} -static
            WORKING_DIRECTORY ${PHYSX_ROOT_DIR}
            RESULT_VARIABLE GENERATE_RESULT
            COMMAND_ECHO STDOUT
        )

    if(NOT GENERATE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to generate PhysX projects with preset ${PHYSX_PRESET}")
    endif()


    set(PHYSX_BUILD_TARGETS
        PhysX
        PhysXCommon
        PhysXCooking
        PhysXExtensions
        PhysXFoundation
    )
   
    foreach(TARGET ${PHYSX_BUILD_TARGETS})
        message(STATUS "Building PhysX target: ${TARGET} (${CMAKE_BUILD_TYPE})")
        
        execute_process(
            COMMAND cmake --build . --config ${CMAKE_BUILD_TYPE} --target ${TARGET} --parallel
            WORKING_DIRECTORY ${PHYSX_ROOT_DIR}/compiler/${CONFIG_DIRECTORY}
            RESULT_VARIABLE BUILD_RESULT
            OUTPUT_VARIABLE BUILD_OUTPUT
            ERROR_VARIABLE BUILD_ERROR
            COMMAND_ECHO STDOUT
        )
        
        if(NOT BUILD_RESULT EQUAL 0)
            message(FATAL_ERROR "PhysX build failed for target: ${TARGET}\n${BUILD_ERROR}")
        else()
            message(STATUS "Successfully built: ${TARGET}")
        endif()
    endforeach()
    
    set(PHYSX_BUILDED TRUE)
    message(STATUS "PhysX build complete!")

    if(NOT BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to build PhysX ${BUILD_CONFIG}")
    endif()
endif()

if(PHYSICS_AXIS_ENGINE AND PHYSX_BUILDED)
    #find includes
    setup_physx_includes(
        "${PHYSX_ROOT_INCLUDES_DIR}" 
        "${PHYSX_INCLUDES_DIR}" 
        FOUND_PHYSX_INCLUDES
    )

    #find libs
    setup_physx_libs(
        "${PHYSX_ROOT_LIBS_DIR}"
        "${PHYSX_LIBS_DIR}"
        FOUND_PHYSX_LIBS
        PHYSX_LIBS
    )
endif()

if (PHYSICS_AXIS_ENGINE)
    add_compile_definitions(AXIS_ENGINE_INCLUDED)
    add_definition("AXIS_ENGINE_INCLUDED")

    set(PHYSX_INCLUDES_DIR "${Engine_Source}/AxisEngine/External/PhysX/include")
    include_directories(${PHYSX_INCLUDES_DIR})

    message("${Cyan}include .cpp engine_axis_list${ColourReset}")

    recurse_add_cpp_items("${Engine_Source}/AxisEngine" engine_axis_list)
    recurse_copy_headers("${Engine_Source}/AxisEngine" "${Build_Dir}/headers/AxisEngine")

    #copy_file("${Engine_Source}/AxisEngine/Module.cfg" "${Configs_Dir}/AxisEngine/Module.cfg")

    add_library(PHYSICS_AXIS_ENGINE STATIC ${engine_axis_list})

    message(${PHYSX_LIBS} SDFFS)

    target_compile_definitions(PHYSICS_AXIS_ENGINE PRIVATE PX_PHYSX_STATIC_LIB)

	target_link_libraries(PHYSICS_AXIS_ENGINE
		PRIVATE ${PHYSX_LIBS}
	)
endif()