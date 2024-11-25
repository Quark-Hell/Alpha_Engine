set(engine_anomaly_list)
option(RENDER_ANOMALY_ENGINE "Build graphics engine. Require RENDER_BASE option" ON)

if(RENDER_ANOMALY_ENGINE AND NOT RENDER_BASE)
    message( FATAL_ERROR "For use RENDER_ANOMALY_ENGINE you should turn on RENDER_BASE" )
endif ()

if (RENDER_BASE AND RENDER_ANOMALY_ENGINE)
    add_compile_definitions(ANOMALY_ENGINE_INCLUDED)
    add_definition("ANOMALY_ENGINE_INCLUDED")

    message("${Cyan}include .cpp engine_anomaly_list${ColourReset}")
    recurse_add_cpp_items(${Engine_Source}/AnomalyEngine engine_anomaly_list)
    recurse_copy_headers("${Engine_Source}/AnomalyEngine" "${Build_Dir}/headers/AnomalyEngine")

    copy_file("${Engine_Source}/AnomalyEngine/Module.cfg" "${Configs_Dir}/AnomalyEngine/Module.cfg")
    recurse_copy_assets("${Engine_Source}/AnomalyEngine/Assets" "${Build_Dir}/Assets")
endif ()