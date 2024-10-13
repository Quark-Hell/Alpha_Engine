# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

if(NOT WIN32)
	string(ASCII 27 Esc)
	set(ColourReset "${Esc}[m")
	set(ColourBold  "${Esc}[1m")
	set(Red         "${Esc}[31m")
	set(Green       "${Esc}[32m")
	set(Yellow      "${Esc}[33m")
	set(Blue        "${Esc}[34m")
	set(Magenta     "${Esc}[35m")
	set(Cyan        "${Esc}[36m")
	set(White       "${Esc}[37m")
	set(BoldRed     "${Esc}[1;31m")
	set(BoldGreen   "${Esc}[1;32m")
	set(BoldYellow  "${Esc}[1;33m")
	set(BoldBlue    "${Esc}[1;34m")
	set(BoldMagenta "${Esc}[1;35m")
	set(BoldCyan    "${Esc}[1;36m")
	set(BoldWhite   "${Esc}[1;37m")
else()
	set(ColourReset "")
	set(ColourBold  "")
	set(Red         "")
	set(Green       "")
	set(Yellow      "")
	set(Blue        "")
	set(Magenta     "")
	set(Cyan        "")
	set(White       "")
	set(BoldRed     "")
	set(BoldGreen   "")
	set(BoldYellow  "")
	set(BoldBlue    "")
	set(BoldMagenta "")
	set(BoldCyan    "")
	set(BoldWhite   "")
endif()

project ("ALPHA_Engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

SET(CMAKE_CXX_FLAGS "-Wall -frtti")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

#Engine source
SET (ALPHA_Engine "${PROJECT_SOURCE_DIR}")
SET (Engine_Source "${ALPHA_Engine}/Engine")
SET (Engine_Assets "${ALPHA_Engine}/Engine_Assets")
SET (Build_Files "${ALPHA_Engine}/Build_Files")
include_directories(${Engine_Source})

#Engine libraries
set (GLFW "${ALPHA_Engine}/GLFW")
include_directories("${GLFW}/include")

set (glm "${ALPHA_Engine}/glm")
include_directories("${glm}/glm")

set (GLEW "${ALPHA_Engine}/GLEW")
include_directories("${GLEW}/include/")

SET (assimp "${ALPHA_Engine}/assimp")
include_directories("${assimp}/include")

SET(STB "${ALPHA_Engine}/STB")
include_directories(${STB})
#Engine libraries

#Game source
set (Game "${PROJECT_BINARY_DIR}")
set (Game_Files_Dest "${Game}/Game")
set (Game_Engine_Dest "${Game_Files_Dest}/ALPHA_Engine")
set (Game_Source_Dest "${Game_Files_Dest}/Source")

set(EXE_DEST "${PROJECT_BINARY_DIR}/ALPHA_Engine")

if(WIN32)
	message("\n${BoldRed}Windows build${ColourReset}\n")
endif ()
if (LINUX)
	message("\n${BoldRed}Linux build${ColourReset}\n")
endif ()


	function(libraries_source src return_list)
file(GLOB_RECURSE templateFiles RELATIVE ${src} "${src}/*.cpp")
    foreach(file ${templateFiles})
		set(copy_src "${src}/${file}")
		list(APPEND return_list "${copy_src}")
    endforeach()
	message("${return_list}\n")
	set(${return_list} "${${return_list}}" PARENT_SCOPE)
endfunction()

set(engine_core_list)
set(engine_binds_list)
set(engine_graphics_engine_list)
set(engine_shader_program_list)
set(engine_user_scripts_list)

set(ANOMALY_ENGINE_INCLUDED ON CACHE BOOL "")
if (ANOMALY_ENGINE_INCLUDED)
	add_compile_definitions(ANOMALY_ENGINE_INCLUDED)

	message("${Cyan}include .cpp engine_graphics_engine_list${ColourReset}")
	libraries_source(${Engine_Source}/Anomaly engine_graphics_engine_list)

	#message("${Cyan}include .cpp engine_binds_list${ColourReset}")
	#libraries_source(${Engine_Source}/Binds engine_binds_list)
endif ()

set(USER_SCRIPTS_REGISTER_INCLUDED ON CACHE BOOL "")
if (USER_SCRIPTS_REGISTER_INCLUDED)
	add_compile_definitions(USER_SCRIPTS_REGISTER_INCLUDED)
	message("${Cyan}include .cpp engine_user_scripts_list${ColourReset}")
	libraries_source(${Engine_Source}/UserScriptsRegister engine_user_scripts_list)
endif ()

message("${Cyan}include .cpp engine_core_list${ColourReset}")
libraries_source(${Engine_Source}/Core engine_core_list)
#libraries_source(${Engine_Source}/ShadersProgram engine_shader_program_list)

add_library (
	ALPHA_Engine STATIC

	${Engine_Source}/ALPHA_Engine.cpp
	#Core
	${engine_core_list}
	${engine_binds_list}
	${engine_graphics_engine_list}
	#${engine_shader_program_list}
	${engine_user_scripts_list}
)

set_target_properties(ALPHA_Engine PROPERTIES PREFIX "")
set_target_properties(ALPHA_Engine PROPERTIES OUTPUT_NAME "ALPHA_Engine")

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

#Configure game folder
function(copy_headers src dest)
	message("${Red}copy headers${ColourReset}")
	file(GLOB_RECURSE templateFiles RELATIVE ${src} "${src}/*.h")
	foreach(templateFile ${templateFiles})
		set(copy_src "${src}/${templateFile}")
		set(copy_dest "${dest}/headers/${templateFile}")	

		message("${Cyan}copy header${ColourReset} ${copy_src} to\n ${copy_dest}")

		add_custom_command(TARGET ALPHA_Engine POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${copy_src}
		${copy_dest}
		)
	endforeach(templateFile)
endfunction()

copy_headers(${Engine_Source} ${Game_Engine_Dest})

function(copy_assets src dest)
	message("\n${Red}copy assets${ColourReset}")
	file(GLOB_RECURSE templateFiles RELATIVE ${src} "${src}/*")
	foreach(templateFile ${templateFiles})
		set(copy_src "${src}/${templateFile}")
		set(copy_dest "${dest}/${templateFile}")	

		message("${Cyan}copy asset${ColourReset} ${copy_src} to\n ${copy_dest}")

		add_custom_command(TARGET ALPHA_Engine POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${copy_src}
		${copy_dest}
		)
	endforeach(templateFile)
endfunction()

copy_assets(${Engine_Assets} "${Game_Engine_Dest}/Engine_Assets")
copy_assets(${Build_Files} "${Game_Source_Dest}")
message("\n")

if(WIN32)
#Stupid method, but it's working
add_custom_command(TARGET ALPHA_Engine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${Game}/ALPHA_Engine.lib
	${Game_Engine_Dest}/lib/ALPHA_Engine.lib

	COMMAND ${CMAKE_COMMAND} -E remove
	${Game}/ALPHA_Engine.lib

	COMMAND ${CMAKE_COMMAND} -E copy
	${GLFW}/glfw3.lib
	${Game_Engine_Dest}/lib/glfw3.lib
)
else()
add_custom_command(TARGET ALPHA_Engine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${Game}/ALPHA_Engine.a
	${Game_Engine_Dest}/lib/ALPHA_Engine.a

	COMMAND ${CMAKE_COMMAND} -E remove
	${Game}/ALPHA_Engine.a

	COMMAND ${CMAKE_COMMAND} -E copy
	${GLFW}/glfw3.a
	${Game_Engine_Dest}/lib/glfw3.a
)
endif()

add_custom_command(TARGET ALPHA_Engine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${Game_Source_Dest}/CMakeLists.txt
	${Game_Files_Dest}/CMakeLists.txt

	COMMAND ${CMAKE_COMMAND} -E remove
	${Game_Source_Dest}/CMakeLists.txt
)

#Configure game folder

target_compile_definitions(ALPHA_Engine
    PRIVATE
      _CRT_SECURE_NO_WARNINGS
    PUBLIC
      $<$<CONFIG:Debug>:OE_DEBUG>
      $<$<CONFIG:RelWithDebInfo>:OE_DEBUG>
      $<$<CONFIG:Release>:OE_RELEASE>
      $<$<CONFIG:MinSizeRel>:OE_RELEASE>
)
