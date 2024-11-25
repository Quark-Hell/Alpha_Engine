if (POLICY CMP0072)
	cmake_policy (SET CMP0072 NEW)
endif(POLICY CMP0072)

add_executable (SimpleGame
		"${Examples_Dir}/SimpleGame/MyScript.cpp"
		"GLAD/glad/src/glad.c"
)

add_dependencies(SimpleGame ALPHA_Engine)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/Examples/SimpleGame/Logs")
recurse_copy_assets(${Engine_Assets} "${CMAKE_BINARY_DIR}/Examples/SimpleGame/Assets")
if(RENDER_ANOMALY_ENGINE)
	recurse_copy_assets(${Engine_Source}/AnomalyEngine/Assets "${CMAKE_BINARY_DIR}/Examples/SimpleGame/Assets")
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

	if(MSVC)
		target_link_libraries(SimpleGame
				PRIVATE ALPHA_Engine
				PRIVATE "${Examples_Build_Dir}/external/glfw3.lib"
				PRIVATE "${Examples_Build_Dir}/external/assimp.lib"
				PRIVATE "${OPENGL_LIBRARIES}"
		)

		copy_file("${Examples_Build_Dir}/external/assimp-vc143-mt.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assimp-vc143-mt.dll")
	elseif(MINGW)
		target_link_libraries(SimpleGame
				PRIVATE ALPHA_Engine
				PRIVATE "${Examples_Build_Dir}/external/glfw3.a"
				PRIVATE "${Examples_Build_Dir}/external/assimp.dll.a"
				PRIVATE "${OPENGL_LIBRARIES}"
		)

		copy_file("${Examples_Build_Dir}/external/libassimp-5.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libassimp-5.dll")
	endif()

else()
	find_package(glfw3 REQUIRED)
	find_package(assimp REQUIRED)

	target_link_libraries(SimpleGame
			PUBLIC ALPHA_Engine
			PRIVATE glfw
			PRIVATE assimp
			PRIVATE "${OPENGL_LIBRARIES}"
	)
endif()
