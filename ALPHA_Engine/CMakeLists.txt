# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("ALPHA_Engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS_RELEASE "-O3") #glfw permission denied

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

SET(CMAKE_CXX_FLAGS "-Wall -frtti")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")


#Engine libraries
set (GLFW "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLFW")
include_directories("${GLFW}/include")

set (glm "${PROJECT_SOURCE_DIR}/ALPHA_Engine/glm")
include_directories("${glm}/glm")

set (GLEW "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLEW")
include_directories("${GLEW}/include/")

SET (assimp "${PROJECT_SOURCE_DIR}/ALPHA_Engine/assimp")
include_directories("${assimp}/include")

SET(STB "${PROJECT_SOURCE_DIR}/ALPHA_Engine/STB")
include_directories(${STB})
#Engine libraries

#Engine source
SET (ALPHA_Engine "${PROJECT_SOURCE_DIR}")
SET (Engine_Source "${ALPHA_Engine}/Engine")
SET (Engine_Assets "${ALPHA_Engine}/Engine_Assets")
SET (Build_Files "${ALPHA_Engine}/Build_Files")
include_directories(${Engine_Source})

#Game source
set (Game "${PROJECT_BINARY_DIR}")
set (Game_Files_Dest "${Game}/Game")
set (Game_Engine_Dest "${Game_Files_Dest}/ALPHA_Engine")
set (Game_Source_Dest "${Game_Files_Dest}/Source")

set(EXE_DEST "${PROJECT_BINARY_DIR}/ALPHA_Engine")


function(libraries_source src return_list)
file(GLOB_RECURSE templateFiles RELATIVE ${src} "${src}/*.cpp")
    foreach(file ${templateFiles})
		set(copy_src "${src}/${file}")
		list(APPEND return_list "${copy_src}")
    endforeach()
	message("include .cpp list ${return_list}\n")
	set(${return_list} "${${return_list}}" PARENT_SCOPE)
endfunction()

set(engine_core_list "")
libraries_source(${Engine_Source}/Core engine_core_list)
set(engine_binds_list)
libraries_source(${Engine_Source}/Binds engine_binds_list)
set(engine_graphics_engine_list)
libraries_source(${Engine_Source}/Graphics_Engine engine_graphics_engine_list)
set(engine_shader_program_list)
libraries_source(${Engine_Source}/ShadersProgram engine_shader_program_list)
set(engine_user_scripts_list)
libraries_source(${Engine_Source}/UserScriptsRegister engine_user_scripts_list)

message(${Engine_Source}/ALPHA_Engine.cpp)

add_library (
	ALPHA_Engine STATIC

	${Engine_Source}/ALPHA_Engine.cpp
	#Core
	${engine_core_list}
	#${engine_binds_list}
	#${engine_graphics_engine_list}
	#${engine_shader_program_list}
	${engine_user_scripts_list}
)

set_target_properties(ALPHA_Engine PROPERTIES PREFIX "")
set_target_properties(ALPHA_Engine PROPERTIES OUTPUT_NAME "ALPHA_Engine")

if(WIN32)
	target_link_libraries(ALPHA_Engine
	PRIVATE OpenGL
	PRIVATE ${GLFW}/glfw3.lib
	PRIVATE ${assimp}/lib/assimp-vc143-mtd.lib
	)
	message("Not support")
endif()
if(LINUX)
	message("Linux build")
	target_link_libraries(ALPHA_Engine
	PRIVATE OpenGL
	PRIVATE ${GLFW}/glfw3.a
	PRIVATE ${assimp}/lib/assimp.so
	)
endif()


#Configure game folder
function(copy_headers src dest)
	message("copy headers")
	file(GLOB_RECURSE templateFiles RELATIVE ${src} "${src}/*.h")
	foreach(templateFile ${templateFiles})
		set(copy_src "${src}/${templateFile}")
		set(copy_dest "${dest}/headers/${templateFile}")	

		message("copy header ${copy_src} to ${copy_dest}")

		add_custom_command(TARGET ALPHA_Engine POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${copy_src}
		${copy_dest}
		)
	endforeach(templateFile)
endfunction()

copy_headers(${Engine_Source} ${Game_Engine_Dest})

function(copy_assets src dest)
	message("copy assets")
	file(GLOB_RECURSE templateFiles RELATIVE ${src} "${src}/*")
	foreach(templateFile ${templateFiles})
		set(copy_src "${src}/${templateFile}")
		set(copy_dest "${dest}/${templateFile}")	

		message("copy asset ${copy_src} to ${copy_dest}")

		add_custom_command(TARGET ALPHA_Engine POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${copy_src}
		${copy_dest}
		)
	endforeach(templateFile)
endfunction()

copy_assets(${Engine_Assets} "${Game_Engine_Dest}/Engine_Assets")
copy_assets(${Build_Files} "${Game_Source_Dest}")

if(WIN32)
#Stupid method, but it's working
add_custom_command(TARGET ALPHA_Engine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${Game}/ALPHA_Engine.lib
	${Game_Engine_Dest}/lib/ALPHA_Engine.lib

	COMMAND ${CMAKE_COMMAND} -E remove
	${Game}/ALPHA_Engine.lib
)
else()
add_custom_command(TARGET ALPHA_Engine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${Game}/ALPHA_Engine.a
	${Game_Engine_Dest}/lib/ALPHA_Engine.a

	COMMAND ${CMAKE_COMMAND} -E remove
	${Game}/ALPHA_Engine.a
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
