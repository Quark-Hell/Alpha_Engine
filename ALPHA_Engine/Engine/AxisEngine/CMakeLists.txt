set(engine_axis_list)
option(PHYSICS_AXIS_ENGINE "Build physics engine." ON)

if (PHYSICS_AXIS_ENGINE)
    add_compile_definitions(AXIS_ENGINE_INCLUDED)
    add_definition("AXIS_ENGINE_INCLUDED")

    message("${Cyan}include .cpp engine_axis_list${ColourReset}")
    recurse_add_cpp_items("${Engine_Source}/AxisEngine" engine_axis_list)
    recurse_copy_headers("${Engine_Source}/AxisEngine" "${Build_Dir}/headers/AxisEngine")

    #copy_file("${Engine_Source}/AxisEngine/Module.cfg" "${Configs_Dir}/AxisEngine/Module.cfg")

    add_library(PHYSICS_AXIS_ENGINE STATIC ${engine_axis_list})
endif ()