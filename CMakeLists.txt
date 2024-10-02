# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("ALPHA_Engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O4") #glfw permission denied

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


#Engine libraries
set (GLFW "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLFW")
include_directories("${GLFWinclude}include/")

set (glm "${PROJECT_SOURCE_DIR}/ALPHA_Engine/glm")
include_directories("${glm}/glm/")

set (GLEW "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLEW")
include_directories("${GLEW}/include/")

SET (assimp "${PROJECT_SOURCE_DIR}/ALPHA_Engine/assimp")
include_directories("${assimp}/include/assimp/")

SET(STB "${PROJECT_SOURCE_DIR}/ALPHA_Engine/STB")
include_directories(${STB})
#Engine libraries

#Engine source
SET (ALPHA_Engine "${PROJECT_SOURCE_DIR}/ALPHA_Engine")
SET (Engine_Source "${ALPHA_Engine}/Engine")
SET (Engine_Assets "${ALPHA_Engine}/Engine_Assets")
SET (Build_Files "${ALPHA_Engine}/Build_Files")
include_directories(${Engine_Source})

#Game source
set (Game "${PROJECT_BINARY_DIR}")
set (Game_Engine_Dest "${Game}/ALPHA_Engine")


set(EXE_DEST "${PROJECT_BINARY_DIR}/ALPHA_Engine")


function(libraries_source src return_list)
message("include .cpp")
file(GLOB_RECURSE templateFiles RELATIVE ${src} "${src}/*.cpp")
    foreach(file ${templateFiles})
		set(copy_src "${src}/${file}")
		message("include ${copy_src}")
    endforeach()
	message("list ${return_list}")
endfunction()

set(engine_core_list)
libraries_source(${Engine_Source}/Core engine_core_list)
set(engine_binds_list)
libraries_source(${Engine_Source}/Binds engine_binds_list)
set(engine_graphics_engine_list)
libraries_source(${Engine_Source}/Graphics_Engine engine_graphics_engine_list)
set(engine_shader_program_list)
libraries_source(${Engine_Source}/ShadersProgram engine_shader_program_list)
set(engine_user_scripts_list)
libraries_source(${Engine_Source}/UserScriptsRegister engine_user_scripts_list)

add_library (
	ALPHA_Engine STATIC
	${Engine_Source}/ALPHA_Engine.cpp

	#Core
	${engine_core_list}
	${engine_binds_list}
	${engine_graphics_engine_list}
	${engine_shader_program_list}
	${engine_user_scripts_list}
)

target_link_libraries(ALPHA_Engine 
PRIVATE ${GLFW}/glfw3.lib
PRIVATE ${GLEW}/glew32s.lib
PRIVATE opengl32.lib
PRIVATE ${assimp}/lib/assimp-vc143-mtd.lib
)


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
copy_assets(${Build_Files} "${Game}/Source")

#Stupid method, but it's working
add_custom_command(TARGET ALPHA_Engine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${Game}/ALPHA_Engine.lib
	${Game_Engine_Dest}/lib/ALPHA_Engine.lib

	COMMAND ${CMAKE_COMMAND} -E remove
	${Game}/ALPHA_Engine.lib
)

add_custom_command(TARGET ALPHA_Engine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${Game}/Source/CMakeLists.txt
	${Game}/CMakeLists.txt

	COMMAND ${CMAKE_COMMAND} -E remove
	${Game}/Source/CMakeLists.txt
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