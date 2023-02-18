# CMakeList.txt : CMake project for ALPHA_Engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


SET (ALPHA_Engine "${PROJECT_SOURCE_DIR}/ALPHA_Engine/")
SET (assimpLIB "${PROJECT_SOURCE_DIR}/ALPHA_Engine/assimp/lib/")
SET (assimpINCLUDE "${PROJECT_SOURCE_DIR}/ALPHA_Engine/assimp/include/")
SET (Engine "${PROJECT_SOURCE_DIR}/ALPHA_Engine/Engine/")
SET (Game "${PROJECT_SOURCE_DIR}/ALPHA_Engine/Game/")

SET (SFML "${PROJECT_SOURCE_DIR}/ALPHA_Engine/SFML-2.5.1/")
SET (SFMLlib "${PROJECT_SOURCE_DIR}/ALPHA_Engine/SFML-2.5.1/lib/")
SET (SFMLinclude "${PROJECT_SOURCE_DIR}/ALPHA_Engine/SFML-2.5.1/include/")

find_package(SFML 2.5.1 REQUIRED COMPONENTS system window graphics PATHS ${SFML})

find_package(OpenGL)
find_package(assimp)

#include_directories(${assimpLIB})
include_directories(${assimpINCLUDE})
include_directories(${Engine})
include_directories(${Game})

include_directories(${SFML})
#include_directories(${SFMLlib})
include_directories(${SFMLinclude})

add_library(Engine 
${SFMLinclude}SFML/Window.hpp
${SFMLinclude}SFML/OpenGL.hpp
${SFMLinclude}SFML/Graphics.hpp

${assimpINCLUDE}assimp/Importer.hpp
${assimpINCLUDE}assimp/scene.h
${assimpINCLUDE}assimp/postprocess.h

${Engine}Basical_Type.cpp  
${Engine}Basical_Type.h
${Engine}Binds.cpp
${Engine}Binds.h
${Engine}Camera.cpp
${Engine}Camera.h
${Engine}Collision.cpp
${Engine}Collision.h
${Engine}Graphic_Engine.cpp
${Engine}Graphic_Engine.h
${Engine}Mesh.cpp
${Engine}Mesh.h
${Engine}Collision.h
${Engine}Collision.cpp
${Engine}Physics.h
${Engine}Physics.cpp

${Game}GameModels.cpp
${Game}GameModels.h
 "Engine/Timer.cpp" "Engine/Timer.h" "Engine/Alghoritms.h" "Engine/Alghoritms.cpp" "Engine/Material.h" "Engine/Material.cpp" "Engine/Texture.cpp" "Engine/Texture.h"  "Engine/Vectors.cpp" "Engine/Vectors.h"  "Engine/Matrix.h" "Engine/Matrix.cpp"   "Engine/Geometry.h" "Engine/Geometry.cpp")

target_link_libraries(Engine
PRIVATE ${SFMLlib}sfml-graphics.lib
PRIVATE ${SFMLlib}sfml-system.lib
PRIVATE ${SFMLlib}sfml-window.lib
PRIVATE ${assimpLIB}assimp-vc143-mtd.lib
)

set(dll_Files "${PROJECT_SOURCE_DIR}/ALPHA_Engine/.dll")
set(GameModels "${PROJECT_SOURCE_DIR}/ALPHA_Engine/Models")
set(EXE_DEST "${PROJECT_BINARY_DIR}/ALPHA_Engine")

file(GLOB SOURCES "${Engine}*.cpp" "${Game}*.cpp")

# Add source to this project's executable.
add_executable (ALPHA_Engine 
ALPHA_Engine.cpp
ALPHA_Engine.h

${SOURCES}

${SFMLinclude}SFML/Window.hpp
${SFMLinclude}SFML/OpenGL.hpp
${SFMLinclude}SFML/Graphics.hpp

${assimpINCLUDE}assimp/Importer.hpp
${assimpINCLUDE}assimp/scene.h
${assimpINCLUDE}assimp/postprocess.h
 "Engine/Timer.cpp" "Engine/Timer.h" "Engine/Alghoritms.h" "Engine/Alghoritms.cpp" "Engine/Material.h" "Engine/Material.cpp" "Engine/Texture.cpp" "Engine/Texture.h"  "Engine/Vectors.cpp" "Engine/Vectors.h"  "Engine/Matrix.h" "Engine/Matrix.cpp"   "Engine/Geometry.h" "Engine/Geometry.cpp")

target_link_libraries(ALPHA_Engine 
PRIVATE sfml-graphics
PRIVATE sfml-system
PRIVATE sfml-window
PRIVATE ${assimpLIB}assimp-vc143-mtd.lib
)

add_custom_target(copy_dll ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${dll_Files}
	${EXE_DEST}
	DEPENDS ${dll_Files}
	COMMENT "Copying resources to ${EXE_DEST}"
)

add_custom_target(copy_models ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${GameModels}
	${EXE_DEST}/Models
	DEPENDS ${dll_Files}
	COMMENT "Copying resources to ${EXE_DEST}/Models"
)

# TODO: Add tests and install targets if needed.
