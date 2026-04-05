if (POLICY CMP0072)
	cmake_policy (SET CMP0072 NEW)
endif(POLICY CMP0072)

set (GAME_SOURCE "${CMAKE_CURRENT_LIST_DIR}")

set (GAME_BUILD_PATH "${OUTPUT_BINARY_DIR}/Examples/SimpleGame")
set (GAME_ASSETS_PATH "${GAME_BUILD_PATH}/Assets")

add_compile_definitions(GAME_ASSETS_PATH="${GAME_ASSETS_PATH}")

add_executable (SimpleGame
		"${GAME_SOURCE}/SimpleGame/EngineScripts/MyScript.cpp"
		"${GAME_SOURCE}/SimpleGame/EngineScripts/Player.cpp"
		"${GAME_SOURCE}/SimpleGame/EngineScripts/WorldBuilder.cpp"

		"${GAME_SOURCE}/SimpleGame/Windows/WindowsSettings.cpp"
		"${GAME_SOURCE}/SimpleGame/Modules.cpp"
)
if(TARGET ANOMALY_ENGINE)
    list(APPEND SOURCES "${GAME_SOURCE}/SimpleGame/External/glad/src/glad.c")
endif()

set_target_properties(SimpleGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${GAME_BUILD_PATH}"
)

add_dependencies(SimpleGame ALPHA_ENGINE)
target_include_directories(SimpleGame PRIVATE "${GAME_SOURCE}/SimpleGame")
target_include_directories(SimpleGame PRIVATE "${GAME_SOURCE}/External")
target_include_directories(SimpleGame PRIVATE "${GAME_SOURCE}/External/glad/include")


file(MAKE_DIRECTORY "${GAME_BUILD_PATH}/Logs")
recurse_copy_assets("${OUTPUT_BINARY_DIR}/Engine/Assets" "${GAME_ASSETS_PATH}")
recurse_copy_assets("${GAME_SOURCE}/SimpleGame/Assets" "${GAME_ASSETS_PATH}")
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

function(link_if_exists target dependency compile_flag)
    if(TARGET ${dependency})
        target_link_libraries(${target} PRIVATE ${dependency})
		target_compile_definitions(${target} PRIVATE ${compile_flag})
    endif()
endfunction()


find_package(OpenGL REQUIRED)

if(WIN32)
	set(PHYSX_LIBS_GAME)

	if(MSVC)
		target_link_libraries(SimpleGame
				#PUBLIC AXIS_ENGINE
				PRIVATE ALPHA_ENGINE

				PRIVATE ${PHYSX_LIBS_GAME}
				PRIVATE ${OPENGL_LIBRARIES}
		)

		link_if_exists(SimpleGame USER_SCRIPTS_REGISTER USER_SCRIPTS_REGISTER_INCLUDED)
		link_if_exists(SimpleGame WINDOWS_MANAGER WINDOWS_MANAGER_INCLUDED)
		link_if_exists(SimpleGame ANOMALY_ENGINE ANOMALY_ENGINE_INCLUDED)
		link_if_exists(SimpleGame BINDS_ENGINE BINDS_ENGINE_INCLUDED)
		link_if_exists(SimpleGame SONAR_ENGINE SONAR_ENGINE_INCLUDED)
		link_if_exists(SimpleGame AXIS_ENGINE AXIS_ENGINE_INCLUDED)
	elseif(MINGW)
		target_link_libraries(SimpleGame
				PUBLIC USER_SCRIPTS_REGISTER
				PUBLIC AXIS_ENGINE
				PUBLIC BINDS_ENGINE
				PUBLIC WINDOWS_MANAGER
				PUBLIC ANOMALY_ENGINE
				PUBLIC SONAR_ENGINE
				PRIVATE ALPHA_ENGINE

				PRIVATE ${PHYSX_LIBS_GAME}
				PRIVATE ${OPENGL_LIBRARIES}
		)

	endif()
else()
	find_package(glfw3 REQUIRED)
	find_package(PhysX REQUIRED)

	target_link_libraries(SimpleGame
			PUBLIC USER_SCRIPTS_REGISTER
			PUBLIC AXIS_ENGINE
			PUBLIC BINDS_ENGINE
			PUBLIC WINDOWS_MANAGER
			PUBLIC ANOMALY_ENGINE
			PUBLIC SONAR_ENGINE
			PUBLIC ALPHA_ENGINE

			PRIVATE glfw
			PRIVATE "${OPENGL_LIBRARIES}"
	)
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")