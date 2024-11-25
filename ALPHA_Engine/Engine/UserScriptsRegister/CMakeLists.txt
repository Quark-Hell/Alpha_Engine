option(USER_SCRIPTS_REGISTER "Build user scripts register" ON)
set(engine_user_scripts_list)

if (USER_SCRIPTS_REGISTER)
    add_compile_definitions(USER_SCRIPTS_REGISTER_INCLUDED)
    add_definition("USER_SCRIPTS_REGISTER_INCLUDED")

    message("${Cyan}include .cpp engine_user_scripts_list${ColourReset}")
    recurse_add_cpp_items("${Engine_Source}/UserScriptsRegister" engine_user_scripts_list)
    recurse_copy_headers("${Engine_Source}/UserScriptsRegister" "${Build_Dir}/headers/UserScriptsRegister")

    copy_file("${Engine_Source}/UserScriptsRegister/Module.cfg" "${Configs_Dir}/UserScriptsRegister/Module.cfg")
endif ()