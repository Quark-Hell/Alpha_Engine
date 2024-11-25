option(Build_Examples "Build examples" ON)

#Examples
set(Examples_Dir "${ALPHA_Engine}/Examples")
message(${Examples_Dir})

if(Build_Examples)
    set(Examples_Build_Dir "${CMAKE_BINARY_DIR}/Examples")

    include("${Examples_Dir}/SimpleGame/CMakeLists.txt")
    include("${Examples_Dir}/SimpleModule/CMakeLists.txt")
endif()