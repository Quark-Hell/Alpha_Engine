if (Build_Examples)
    if (POLICY CMP0072)
        cmake_policy (SET CMP0072 NEW)
    endif(POLICY CMP0072)

    add_executable (SimpleModule
            "${Examples_Dir}/SimpleModule/MyModule.cpp"
            "${Examples_Dir}/SimpleModule/MyModuleData.cpp"
            "${Examples_Dir}/SimpleModule/Registration.cpp")

    add_dependencies(SimpleModule ALPHA_Engine)

    target_link_libraries(SimpleModule
            PRIVATE ALPHA_Engine
    )
endif ()
