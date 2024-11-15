cmake_minimum_required (VERSION 3.8)

project ("Game")

if (POLICY CMP0072)
	cmake_policy (SET CMP0072 NEW)
endif(POLICY CMP0072)

if(WIN32)
	message("\n${BoldRed}Windows build${ColourReset}\n")
	add_compile_definitions(PLATFORM=Windows)
endif ()
if (LINUX)
	message("\n${BoldRed}Linux build${ColourReset}\n")
	add_compile_definitions(PLATFORM=Linux)
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "-Wall -frtti")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

set (Game_Source "${PROJECT_SOURCE_DIR}/Source")
include_directories("${Game_Source}")

set (Engine "${PROJECT_SOURCE_DIR}/ALPHA_Engine")
set (Engine_Assets "${Engine}/Engine_Assets")

set (Engine_Headers "${Engine}/headers")
include_directories("${Engine_Headers}")

set (GLM "${Engine}/GLM")
include_directories("${GLM}")

set (GLEW "${Engine}/GLEW")
include_directories("${GLEW}")

set (Engine_Libs "${Engine}/lib")

include("${Game_Source}/IncludedModules.cmake")

add_executable(Game
		${Game_Source}/MyScript.cpp
)
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/Logs")
find_package(OpenGL REQUIRED)

if(WIN32)
	target_link_libraries(Game
			PRIVATE ${Engine_Libs}/ALPHA_Engine.lib
			PRIVATE ${Engine_Libs}/glfw3dll.lib
			PRIVATE ${Engine_Libs}/glew32s.lib
			PRIVATE ${Engine_Libs}/assimp-vc143-mt.lib
			PRIVATE ${OPENGL_LIBRARIES}
	)
else()
	find_package(GLEW REQUIRED)

	target_link_libraries(Game
			PRIVATE ${Engine_Libs}/ALPHA_Engine.a
			PRIVATE ${Engine_Libs}/glfw3.a
			PRIVATE GLEW::GLEW
			PRIVATE ${Engine_Libs}/libassimp.so.5
			PRIVATE ${OPENGL_LIBRARIES}
	)
endif()

function(copy_assets src dest)
	message("\n${Red}copy assets${ColourReset}")
	file(GLOB_RECURSE templateFiles RELATIVE ${src} "${src}/*")
	foreach(templateFile ${templateFiles})
		set(copy_src "${src}/${templateFile}")
		set(copy_dest "${dest}/${templateFile}")	

		message("${Cyan}copy asset${ColourReset} ${copy_src} to\n ${copy_dest}")

		add_custom_command(TARGET Game POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${copy_src}
		${copy_dest}
		)
	endforeach(templateFile)
endfunction()


copy_assets("${Engine_Assets}"	"${PROJECT_BINARY_DIR}/ALPHA_Engine/Engine_Assets")


if(WIN32)
	#I did'n know why command copy_asset does not work in this case
	add_custom_command(TARGET Game POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${Engine}/lib/glfw3.dll"
	"${PROJECT_BINARY_DIR}/"
	)
	
	add_custom_command(TARGET Game POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${Engine}/lib/assimp-vc143-mt.dll"
	"${PROJECT_BINARY_DIR}/"
	)
endif()