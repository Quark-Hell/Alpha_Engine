file(WRITE "${Build_Dir}/config.cfg" "")

#Modules
include("Engine/Render/CMakeLists.txt")
include("Engine/BindsEngine/CMakeLists.txt")
include("Engine/UserScriptsRegister/CMakeLists.txt")
#Modules

#Core
set(engine_core_list)
message("${Cyan}include .cpp engine_core_list${ColourReset}")

recurse_add_cpp_items("${Engine_Source}/Core" engine_core_list)
recurse_copy_headers("${Engine_Source}/Core" "${Build_Dir}/headers/Core")



option(LOGGER "Build logger" ON)
if(LOGGER)
	add_compile_definitions(LOGGER_INCLUDED)
endif()
#Core

add_library (
        ALPHA_Engine STATIC
        "Engine/ALPHA_Engine.cpp"

        ##Core
        "${engine_core_list}"

        ##Engine Modules
        "${engine_render_list}"
        "${engine_anomaly_list}"
        "${engine_binds_list}"
        "${engine_user_scripts_list}"
)

set_target_properties(ALPHA_Engine PROPERTIES PREFIX "")
set_target_properties(ALPHA_Engine PROPERTIES OUTPUT_NAME "ALPHA_Engine")

#copy_file("${Engine_Source}/EngineConfig.h" "${Game_Engine_Dest}/headers/EngineConfig.h")

