# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

cmake_minimum_required (VERSION 3.31)

project ("ALPHA_Engine")

include("CMakeColorsOutput.txt")
include("CMakeVariables.txt")

include("CMakeFunctions.txt")

if(WIN32)
	message("\n${BoldRed}Windows build${ColourReset}\n")
	add_compile_definitions(WINDOWS)
endif ()
if (LINUX)
	message("\n${BoldRed}Linux build${ColourReset}\n")
	add_compile_definitions(LINUX)
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_definitions(-DNDEBUG)
else()
    add_definitions(-D_DEBUG)
endif()


#SET(CMAKE_CXX_FLAGS "-Wall -frtti")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

#SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g -fsanitize=undefined -fsanitize=address")

#Engine
include("Engine/CMakeLists.txt") 

target_compile_definitions(ALPHA_Engine
		PRIVATE
		_CRT_SECURE_NO_WARNINGS
		PUBLIC
		$<$<CONFIG:Debug>:OE_DEBUG>
		$<$<CONFIG:RelWithDebInfo>:OE_DEBUG>
		$<$<CONFIG:Release>:OE_RELEASE>
		$<$<CONFIG:MinSizeRel>:OE_RELEASE>
)

#Utility
#include("Utility/AlphaConfigurator/CMakeLists.txt")
#include("Utility/EngineDataCollector/CMakeLists.txt")

include("Engine/UserScriptsRegister/CMakeLists.txt")
include("Engine/AxisEngine/CMakeLists.txt")
include("Engine/WindowsManager/CMakeLists.txt")
include("Engine/BindsEngine/CMakeLists.txt")
include("Engine/AnomalyEngine/CMakeLists.txt")
include("Engine/SonarEngine/CMakeLists.txt")

#Example
include("Examples/CMakeLists.txt")

#Tests
#include("Tests/CMakeLists.txt")
