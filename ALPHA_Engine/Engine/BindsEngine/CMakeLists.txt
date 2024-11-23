option(RENDER_BINDS_ENGINE "Build input system. Require RENDER_BASE option" ON)
set(engine_binds_list)

if(RENDER_BINDS_ENGINE AND NOT RENDER_BASE)
    message(FATAL_ERROR "For use RENDER_BINDS_ENGINE you should turn on RENDER_BASE" )
endif ()

if (RENDER_BASE AND RENDER_BINDS_ENGINE)
    add_compile_definitions(BINDS_ENGINE_INCLUDED)
    add_definition("BINDS_ENGINE_INCLUDED")

    message("${Cyan}include .cpp engine_binds_list${ColourReset}")
    recurse_add_cpp_items("${Engine_Source}/BindsEngine" engine_binds_list)
    recurse_copy_headers("${Engine_Source}/BindsEngine" "${Build_Dir}/headers/BindsEngine")
endif ()

