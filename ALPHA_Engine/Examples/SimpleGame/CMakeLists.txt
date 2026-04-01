set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Examples/SimpleGame")
if (POLICY CMP0072)
	cmake_policy (SET CMP0072 NEW)
endif(POLICY CMP0072)

SET (Game_Source "${CMAKE_CURRENT_LIST_DIR}")

SET (GAME_BUILD_PATH "${CMAKE_BINARY_DIR}/Examples/SimpleGame")
SET (GAME_ASSETS_PATH "${GAME_BUILD_PATH}/Assets")

include_directories("${Game_Source}")
add_compile_definitions(GAME_ASSETS_PATH="${GAME_ASSETS_PATH}")

add_executable (SimpleGame
		"${Examples_Dir}/SimpleGame/EngineScripts/MyScript.cpp"
		"${Examples_Dir}/SimpleGame/EngineScripts/Player.cpp"
		"${Examples_Dir}/SimpleGame/EngineScripts/WorldBuilder.cpp"

		"${Examples_Dir}/SimpleGame/Windows/WindowsSettings.cpp"
		"${Examples_Dir}/SimpleGame/Modules.cpp"
		"external/GLAD/glad/src/glad.c")

add_dependencies(SimpleGame ALPHA_Engine)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/Examples/SimpleGame/Logs")
recurse_copy_assets("${Game_Source}/Assets" "${GAME_ASSETS_PATH}")
if(RENDER_ANOMALY_ENGINE)
	recurse_copy_assets(${Engine_Source}/AnomalyEngine/Assets "${GAME_ASSETS_PATH}")
endif ()

target_compile_definitions(SimpleGame
		PRIVATE
		_CRT_SECURE_NO_WARNINGS
		PUBLIC
		$<$<CONFIG:Debug>:OE_DEBUG>
		$<$<CONFIG:RelWithDebInfo>:OE_DEBUG>
		$<$<CONFIG:Release>:OE_RELEASE>
		$<$<CONFIG:MinSizeRel>:OE_RELEASE>
)

find_package(OpenGL REQUIRED)

if(WIN32)
	include(CMakeCloneDependencies.txt)

	set(PHYSX_LIBS_GAME)

	if(MSVC)
		target_link_libraries(SimpleGame
				PUBLIC USER_SCRIPTS_REGISTER
				PUBLIC PHYSICS_AXIS_ENGINE
				PUBLIC BINDS_ENGINE
				PUBLIC RENDER_BASE
				PUBLIC ANOMALY_ENGINE
				PUBLIC AUDIO_SONAR_ENGINE
				PRIVATE ALPHA_Engine

				PRIVATE ${PHYSX_LIBS_GAME}

				PRIVATE "${Examples_Build_Dir}/external/glfw3.lib"
				PRIVATE "${Examples_Build_Dir}/external/assimp.lib"
				PRIVATE "${OPENGL_LIBRARIES}"
		)

		copy_file("${Examples_Build_Dir}/external/assimp-vc143-mt.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assimp-vc143-mt.dll")
		copy_file("${Examples_Build_Dir}/external/OpenAL32.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenAL32.dll")
	elseif(MINGW)
		target_link_libraries(SimpleGame
				PUBLIC USER_SCRIPTS_REGISTER
				PUBLIC PHYSICS_AXIS_ENGINE
				PUBLIC BINDS_ENGINE
				PUBLIC RENDER_BASE
				PUBLIC ANOMALY_ENGINE
				PUBLIC AUDIO_SONAR_ENGINE
				PRIVATE ALPHA_Engine

				PRIVATE ${PHYSX_LIBS_GAME}

				PRIVATE "${Examples_Build_Dir}/external/glfw3.a"
				PRIVATE "${Examples_Build_Dir}/external/assimp.dll.a"
				PRIVATE "${OPENGL_LIBRARIES}"
		)

		copy_file("${Examples_Build_Dir}/external/libassimp-5.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libassimp-5.dll")
		copy_file("${Examples_Build_Dir}/external/OpenAL32.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpenAL32.dll")
	endif()

else()
	find_package(glfw3 REQUIRED)
	find_package(assimp REQUIRED)
	find_package(PhysX REQUIRED)

	target_link_libraries(SimpleGame
			PUBLIC USER_SCRIPTS_REGISTER
			PUBLIC PHYSICS_AXIS_ENGINE
			PUBLIC BINDS_ENGINE
			PUBLIC RENDER_BASE
			PUBLIC ANOMALY_ENGINE
			PUBLIC AUDIO_SONAR_ENGINE
			PUBLIC ALPHA_Engine

			PRIVATE glfw
			PRIVATE assimp
			PRIVATE "${OPENGL_LIBRARIES}"
	)
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")