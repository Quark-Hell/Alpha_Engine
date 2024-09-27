# CMakeList.txt : CMake project for Game, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set (Game "${PROJECT_SOURCE_DIR}/")

# Add source to this project's executable.
add_executable (MyGame 
${Game}Game/GameFolder/Game.h
${Game}Game/GameFolder/Game.cpp
)

set (dll_Files "${PROJECT_SOURCE_DIR}/Game/ALPHA_Engine/ALPHA_Engine.dll")
set (EXE_DEST "${PROJECT_BINARY_DIR}/Game")
set (Engine "${PROJECT_SOURCE_DIR}/Game/ALPHA_Engine")

set(Game "${PROJECT_SOURCE_DIR}/Game")

include_directories(${Game})
include_directories(${Engine})


target_link_libraries(MyGame 
PRIVATE ${Game}/ALPHA_Engine.lib
)

add_custom_target(copy_engine ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${Game}/ALPHA_Engine
	${EXE_DEST}/ALPHA_Engine
	COMMENT "Copying resources to ${EXE_DEST}"
)

add_custom_target(copy_engine_library ALL
	COMMAND ${CMAKE_COMMAND} -E copy
	${Game}/ALPHA_Engine.dll
	${EXE_DEST}/ALPHA_Engine.dll
	COMMENT "Copying resources to ${EXE_DEST}"
)


#add_custom_target(copy_dll ALL
#	COMMAND ${CMAKE_COMMAND} -E copy_directory
#	${dll_Files}
#	${EXE_DEST}
#	DEPENDS ${dll_Files}
#	COMMENT "Copying resources to ${EXE_DEST}"
#)

# TODO: Add tests and install targets if needed.
