option(RENDER_BASE "Build base render" ON)
set(engine_windows_manager_list)

if(RENDER_BASE)
    add_compile_definitions(WINDOWS_MANAGER_INCLUDED)
    add_definition("WINDOWS_MANAGER_INCLUDED")

    message("${Cyan}include .cpp engine_windows_manager_list${ColourReset}")
    recurse_add_cpp_items("${Engine_Source}/WindowsManager" engine_windows_manager_list)
    recurse_copy_headers("${Engine_Source}/WindowsManager" "${Build_Dir}/headers/WindowsManager")
endif()