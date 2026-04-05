option(USER_SCRIPTS_REGISTER "Build user scripts register" ON)
set(engine_user_scripts_list)

if (USER_SCRIPTS_REGISTER)
    set (USER_SCRIPT_REGISTER_SOURCE "${CMAKE_CURRENT_LIST_DIR}")
    add_compile_definitions(USER_SCRIPTS_REGISTER_INCLUDED)

    message("${Cyan}include .cpp engine_user_scripts_list${ColourReset}")
    recurse_add_cpp_items("${USER_SCRIPT_REGISTER_SOURCE}/UserScriptsRegister" engine_user_scripts_list)
    recurse_copy_headers("${USER_SCRIPT_REGISTER_SOURCE}/UserScriptsRegister" "${BUILD_DIR}/headers/UserScriptsRegister")

    add_library(USER_SCRIPTS_REGISTER STATIC ${engine_user_scripts_list})

    if(LOGGER_INCLUDED)
        target_compile_definitions(USER_SCRIPTS_REGISTER PRIVATE LOGGER_INCLUDED)
    endif()

    target_include_directories(USER_SCRIPTS_REGISTER
        PUBLIC "${USER_SCRIPT_REGISTER_SOURCE}"
        PRIVATE "${Engine_Source}/Core"
        PRIVATE "${Engine_Source}/Core/External"
    )
endif ()