# CMakeList.txt : CMake project for ALPHA_Engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (GLEW "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLEW/")
set (GLFW "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLFW/")
set (glm "${PROJECT_SOURCE_DIR}/ALPHA_Engine/glm/")

set (GLEWinclude "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLEW/include/")
set (GLFWinclude "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLFW/include/")
set (glmInclude "${PROJECT_SOURCE_DIR}/ALPHA_Engine/glm/glm/")

SET (ALPHA_Engine "${PROJECT_SOURCE_DIR}/ALPHA_Engine/")
SET (assimpLIB "${PROJECT_SOURCE_DIR}/ALPHA_Engine/assimp/lib/")
SET (assimpINCLUDE "${PROJECT_SOURCE_DIR}/ALPHA_Engine/assimp/include/")
SET (Engine "${PROJECT_SOURCE_DIR}/ALPHA_Engine/Engine/")
SET (Game "${PROJECT_SOURCE_DIR}/ALPHA_Engine/Game/")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/GLFW")
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLFW/")

find_library(GLEW glew)
#find_package(glew REQUIRED)
#find_package(GLFW REQUIRED)
#find_package(OpenGL REQUIRED)
#find_package(ASSIMP REQUIRED)

include_directories(${GLEWinclude})
include_directories(${GLFWinclude})
include_directories(${glmInclude})

include_directories(${assimpINCLUDE})
include_directories(${Engine})
include_directories(${Game})
include_directories(${glm})

include_directories(${SFML})
include_directories(${SFMLinclude})

set(dll_Files "${PROJECT_SOURCE_DIR}/ALPHA_Engine/.dll")
set(GameModels "${PROJECT_SOURCE_DIR}/ALPHA_Engine/Models")
set(EXE_DEST "${PROJECT_BINARY_DIR}/ALPHA_Engine")

# Add source to this project's executable.
add_executable (ALPHA_Engine 
ALPHA_Engine.cpp
ALPHA_Engine.h
${assimpINCLUDE}assimp/Importer.hpp
${assimpINCLUDE}assimp/scene.h
${assimpINCLUDE}assimp/postprocess.h

${Engine}Alghoritms.h
${Engine}Basical_Type.h
${Engine}Collision.h
${Engine}Graphic_Engine.h
${Engine}Material.h
${Engine}Matrix.h  
${Engine}Object.h 
${Engine}Texture.h 
${Engine}Timer.h
${Engine}Vectors.h
${Engine}World.h  

${Engine}Modules/Camera.h
${Engine}Modules/Geometry.h
${Engine}Modules/Mesh.h
${Engine}Modules/Module.h
${Engine}Modules/Physics.h
"Game/GameModels.h" 
"Engine/AdditionalMath.h" 
"Engine/AdditionalMath.cpp" 
"Engine/Modules/BoxCollider.cpp" 
"Engine/Modules/BoxCollider.h"
${glm}glm.hpp
)

target_link_libraries(ALPHA_Engine 
PRIVATE ${GLFW}/glfw3.lib
PRIVATE ${GLEW}/glew32s.lib
PRIVATE opengl32.lib
PRIVATE ${assimpLIB}assimp-vc143-mtd.lib
)

target_compile_options(ALPHA_Engine PUBLIC "/Zc:__cplusplus")

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
