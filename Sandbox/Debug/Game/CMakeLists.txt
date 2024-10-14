cmake_minimum_required (VERSION 3.8)

project ("Game")

if (POLICY CMP0072)
	cmake_policy (SET CMP0072 NEW)
endif(POLICY CMP0072)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (Game_Source "${PROJECT_SOURCE_DIR}/Source")
include_directories("${Game_Source}")

set (Engine "${PROJECT_SOURCE_DIR}/ALPHA_Engine")
set (Engine_Assets "${Engine}/Engine_Assets")

set (Engine_Headers "${Engine}/headers")
include_directories("${Engine_Headers}")

set (Engine_Libs "${Engine}/lib")

include("${Game_Source}/IncludedModules.cmake")

add_executable(Game
		${Game_Source}/MyScript.cpp
)

find_package(OpenGL REQUIRED)

if(WIN32)
	target_link_libraries(Game
			PRIVATE ${Engine_Libs}/ALPHA_Engine.lib
			PRIVATE ${Engine_Libs}/glfw3.lib
			PRIVATE ${Engine_Libs}/glew32.lib
			PRIVATE ${OPENGL_LIBRARIES}
	)
else()
	target_link_libraries(Game
			PRIVATE ${Engine_Libs}/ALPHA_Engine.a
			PRIVATE ${Engine_Libs}/glfw3.a
			PRIVATE ${Engine_Libs}/libGLEW.a
			PRIVATE ${OPENGL_LIBRARIES}
	)
endif()
