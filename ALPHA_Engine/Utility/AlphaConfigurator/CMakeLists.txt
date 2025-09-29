option(ALPHA_Configurator_Build "" OFF)

if(ALPHA_Configurator_Build) 
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Build")
    
    set(CONFIG_OUTPUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/")
    add_compile_definitions(CONFIG_OUTPUT="${CONFIG_OUTPUT}")
    
    include_directories("Utility/AlphaConfigurator")
    
    set(ALPHA_Configurator_SOURCES
            "Utility/AlphaConfigurator/Configurator.cpp"
            "Utility/AlphaConfigurator/Configurator.h"
            "Utility/AlphaConfigurator/File.cpp"
            "Utility/AlphaConfigurator/File.h"
            "Utility/AlphaConfigurator/SystemRegistrator.cpp"
            "Utility/AlphaConfigurator/SystemRegistrator.h"
            "Utility/AlphaConfigurator/MacrosGenerator.cpp"
            "Utility/AlphaConfigurator/MacrosGenerator.h")
    
    add_executable (
            ALPHA_Configurator
            ${ALPHA_Configurator_SOURCES}
    )
    
    set_target_properties(ALPHA_Configurator PROPERTIES PREFIX "")
    set_target_properties(ALPHA_Configurator PROPERTIES OUTPUT_NAME "ALPHA Configurator")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
endif()