# CMakeList.txt : CMake project for Game, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set (Game "${PROJECT_SOURCE_DIR}/Game/")
include_directories(${Game})

# Add source to this project's executable.
add_executable (MyGame 
${Game}GameFolder/Game.h
${Game}GameFolder/Game.cpp
)

set (dll_Files "${PROJECT_SOURCE_DIR}/Game/ALPHA_Engine/ALPHA_Engine.dll")
set (EXE_DEST "${PROJECT_BINARY_DIR}/Game")
set (Engine "${PROJECT_SOURCE_DIR}/Game/ALPHA_Engine")

set (CMAKE_SKIP_INSTALL_RPATH ON)

include_directories(${Game})
include_directories(${Engine})


target_link_libraries(MyGame 
PRIVATE ${Game}/ALPHA_Engine.lib
)


#add_custom_target(copy_dll ALL
#	COMMAND ${CMAKE_COMMAND} -E copy_directory
#	${dll_Files}
#	${EXE_DEST}
#	DEPENDS ${dll_Files}
#	COMMENT "Copying resources to ${EXE_DEST}"
#)

# TODO: Add tests and install targets if needed.
