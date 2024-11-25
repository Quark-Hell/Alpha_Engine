set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Build")

add_executable (
        ALPHA_Configurator
        "Utility/AlphaConfigurator/Configurator.cpp"
)

set_target_properties(ALPHA_Configurator PROPERTIES PREFIX "")
set_target_properties(ALPHA_Configurator PROPERTIES OUTPUT_NAME "ALPHA Configurator")