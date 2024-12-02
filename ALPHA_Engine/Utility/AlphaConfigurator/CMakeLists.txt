set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Build")

set(USER_FILES "${Examples_Dir}/SimpleGame")

set(CONFIG_SOURCE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Configs")
set(CONFIG_OUTPUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/")

message("${USER_FILES}")

add_compile_definitions(USER_FILES_DIRECTORY="${USER_FILES}")

add_compile_definitions(CONFIG_SOURCE="${CONFIG_SOURCE}")
add_compile_definitions(CONFIG_OUTPUT="${CONFIG_OUTPUT}")

include_directories("Utility/AlphaConfigurator")

add_executable (
        ALPHA_Configurator
        "Utility/AlphaConfigurator/Configurator.cpp"
        "Utility/AlphaConfigurator/Configurator.h"
        "Utility/AlphaConfigurator/File.cpp"
        "Utility/AlphaConfigurator/File.h"
        "Utility/AlphaConfigurator/SystemRegistrator.cpp"
        "Utility/AlphaConfigurator/SystemRegistrator.h")

set_target_properties(ALPHA_Configurator PROPERTIES PREFIX "")
set_target_properties(ALPHA_Configurator PROPERTIES OUTPUT_NAME "ALPHA Configurator")