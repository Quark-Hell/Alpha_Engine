# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

cmake_minimum_required (VERSION 3.8)

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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

SET(CMAKE_CXX_FLAGS "-Wall -frtti")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

include("Engine/CMakeLists.txt") #Build engine core with modules
recurse_copy_assets(${Engine_Assets} "${Build_Dir}/Engine_Assets")

target_compile_definitions(ALPHA_Engine
		PRIVATE
		_CRT_SECURE_NO_WARNINGS
		PUBLIC
		$<$<CONFIG:Debug>:OE_DEBUG>
		$<$<CONFIG:RelWithDebInfo>:OE_DEBUG>
		$<$<CONFIG:Release>:OE_RELEASE>
		$<$<CONFIG:MinSizeRel>:OE_RELEASE>
)

include(Examples/SimpleGame/CMakeLists.txt)

#Utility
include("Utility/AlphaConfigurator/CMakeLists.txt")