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

option(INSTALL_DEPENDENCIES "Set on to automatically install all dependencies" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "-Wall -frtti")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")


include(CMakeVariables.txt)
include(CloneDependencies.txt)

add_executable(Game
		${Game_Source}/MyScript.cpp
)

find_package(OpenGL REQUIRED)

if(WIN32)

	if(MSVC)
		target_link_libraries(Game
				PRIVATE ${Engine_Libs}/ALPHA_Engine.lib
				PRIVATE ${Engine_Libs}/glfw3.lib
				PRIVATE ${Engine_Libs}/glew32s.lib
				PRIVATE ${Engine_Libs}/assimp.lib
				PRIVATE ${OPENGL_LIBRARIES}
		)
	elseif(MINGW)
		target_link_libraries(Game
				PRIVATE ${Engine_Libs}/ALPHA_Engine.a
				PRIVATE ${Engine_Libs}/glfw3.a
				PRIVATE ${Engine_Libs}/glew32.dll.a
				PRIVATE ${Engine_Libs}/assimp.dll.a
				PRIVATE ${OPENGL_LIBRARIES}
		)
	endif()

else()
	find_package(GLEW REQUIRED)

	target_link_libraries(Game
			PRIVATE ${Engine_Libs}/ALPHA_Engine.a
			PRIVATE ${Engine_Libs}/glfw3.a
			PRIVATE ${Engine_Libs}/libassimp.so.5
			PRIVATE GLEW::GLEW
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

add_custom_command(TARGET Game POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/Logs"
)

if(WIN32)
	if(MSVC)
		execute_process(
				COMMAND ${CMAKE_COMMAND} -E copy_if_different
				"${Engine}/lib/assimp.dll"
				"${PROJECT_BINARY_DIR}/assimp-vc143-mt.dll"
		)
	elseif(MINGW)
		execute_process(
				COMMAND ${CMAKE_COMMAND} -E copy_if_different
				"${Engine}/lib/glew32.dll"
				"${PROJECT_BINARY_DIR}/glew32.dll"

				COMMAND ${CMAKE_COMMAND} -E copy_if_different
				"${Engine}/lib/libassimp-5.dll"
				"${PROJECT_BINARY_DIR}/libassimp-5.dll"
		)
	endif()
endif()