option(Build_Examples "Build examples" ON)

#Examples

if(Build_Examples)
    add_subdirectory("${Examples_Source}/SimpleGame")
    #add_subdirectory("${Examples_Source}/SimpleModule")
endif()
