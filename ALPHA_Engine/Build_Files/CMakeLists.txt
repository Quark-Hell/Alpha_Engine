cmake_minimum_required (VERSION 3.8)

project ("Game")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (Game_Source "${PROJECT_SOURCE_DIR}/Source")
include_directories("${Game_Source}")

set (Engine "${PROJECT_SOURCE_DIR}/ALPHA_Engine")
set (Engine_Assets "${Engine}/Engine_Assets")
set (Engine_Headers "${Engine}/headers")
set (Engine_Libs "${Engine}/lib")

add_executable(Game
	${Game_Source}/MyScript.cpp
)

target_link_libraries(Game
PRIVATE ${Engine_Libs}/ALPHA_Engine.lib
)