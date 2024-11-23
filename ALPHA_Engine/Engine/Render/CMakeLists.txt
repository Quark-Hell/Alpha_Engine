#Render
option(RENDER_BASE "Build base render" ON)
option(RENDER_ANOMALY_ENGINE "Build graphics engine. Require RENDER_BASE option" ON)

set(engine_render_list)
set(engine_anomaly_list)

if(RENDER_BASE)
    add_compile_definitions(RENDER_INCLUDED)
    add_definition("RENDER_INCLUDED")

    add_cpp_items(${Engine_Source}/Render/WinManager engine_render_list)

    copy_file("${Engine_Source}/Render/RenderConfig.h" "${Build_Dir}/headers/Render/RenderConfig.h")
    copy_file("${Engine_Source}/Render/WinManager/Window.h" "${Build_Dir}/headers/Render/WinManager/Window.h")
    copy_file("${Engine_Source}/Render/WinManager/WindowsManager.h" "${Build_Dir}/headers/Render/WinManager/WindowsManager.h")
    copy_file("${Engine_Source}/Render/WinManager/WindowsBuffer.h" "${Build_Dir}/headers/Render/WinManager/WindowsBuffer.h")
    copy_file("${Engine_Source}/Render/WinManager/WinManagerConfig.h" "${Build_Dir}/headers/Render/WinManager/WinManagerConfig.h")
endif()

#Include render engine
if (RENDER_BASE AND RENDER_ANOMALY_ENGINE)
	add_compile_definitions(ANOMALY_ENGINE_INCLUDED)
    add_definition("ANOMALY_ENGINE_INCLUDED")

	message("${Cyan}include .cpp engine_anomaly_list${ColourReset}")
	recurse_add_cpp_items(${Engine_Source}/Render/WinManager/AnomalyEngine engine_anomaly_list)
    recurse_copy_headers("${Engine_Source}/Render/WinManager/AnomalyEngine" "${Build_Dir}/headers/Render/WinManager/AnomalyEngine")
endif ()