# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

cmake_minimum_required (VERSION 3.31)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("ALPHA_Engine")

include("CMakeColorsOutput.txt")
include("CMakeFunctions.txt")



# ------------------- Global compiler flags -------------------
if(MSVC)
    # Warning level
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
else()
    # Warning level for GCC/Clang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

set(CMAKE_DEBUG_POSTFIX "")

# ------------------- Configuration-specific flags -------------------
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g")

# Debug
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
    add_compile_options($<$<CONFIG:Debug>:-fsanitize=address>)
    add_link_options($<$<CONFIG:Debug>:-fsanitize=address>)
endif()
# ------------------- /Configuration-specific flags -------------------




set (ALPHA_Engine "${PROJECT_SOURCE_DIR}")
set (Engine_Source "${ALPHA_Engine}/Engine")
set (Examples_Source "${ALPHA_Engine}/Examples")

set (OUTPUT_BINARY_DIR "${CMAKE_BINARY_DIR}/_Output")

set(BUILD_DIR "${OUTPUT_BINARY_DIR}/Engine" CACHE PATH "Custom build dir")
set(LIBRARY_OUTPUT_PATH "${OUTPUT_BINARY_DIR}/Engine/lib")
set(RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_BINARY_DIR}/Examples")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

#Checking platform
if(WIN32)
	message("\n${BoldRed}Windows build${ColourReset}\n")
	add_compile_definitions(WINDOWS)
endif ()
if (LINUX)
	message("\n${BoldRed}Linux build${ColourReset}\n")
	add_compile_definitions(LINUX)
endif ()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_definitions(-DNDEBUG)
else()
    add_definitions(-D_DEBUG)
endif()

#Utility
#include("Utility/AlphaConfigurator/CMakeLists.txt")
#include("Utility/EngineDataCollector/CMakeLists.txt")

add_subdirectory("${Engine_Source}/Core") 
add_subdirectory("${Engine_Source}/UserScriptsRegister") 
add_subdirectory("${Engine_Source}/WindowsManager") 
add_subdirectory("${Engine_Source}/AnomalyEngine")
add_subdirectory("${Engine_Source}/BindsEngine")
add_subdirectory("${Engine_Source}/SonarEngine")
add_subdirectory("${Engine_Source}/AxisEngine")

#Example
add_subdirectory("${Examples_Source}")

#Tests
#include("Tests/CMakeLists.txt")
