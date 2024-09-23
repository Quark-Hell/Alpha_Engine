# CMakeList.txt : CMake project for ALPHA_Engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O4") #glfw permission denied
set (ALPHA "${PROJECT_SOURCE_DIR}")

set (GLEW "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLEW/")
set (GLFW "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLFW/")
set (glm "${PROJECT_SOURCE_DIR}/ALPHA_Engine/glm/")

set (GLEWinclude "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLEW/include/")
set (GLFWinclude "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLFW/include/")
set (glmInclude "${PROJECT_SOURCE_DIR}/ALPHA_Engine/glm/glm/")

SET (ALPHA_Engine "${PROJECT_SOURCE_DIR}/ALPHA_Engine/")
SET (assimpLIB "${PROJECT_SOURCE_DIR}/ALPHA_Engine/assimp/lib/")
SET (assimpINCLUDE "${PROJECT_SOURCE_DIR}/ALPHA_Engine/assimp/include/")
SET (assimp "${PROJECT_SOURCE_DIR}/ALPHA_Engine/assimpB/")

SET (Engine "${PROJECT_SOURCE_DIR}/ALPHA_Engine/Engine/")

SET (Game "${PROJECT_SOURCE_DIR}/ALPHA_Engine/Game/")

SET(STB "${PROJECT_SOURCE_DIR}/ALPHA_Engine/STB/")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/GLFW")
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/ALPHA_Engine/GLFW/")

find_library(GLEW glew)
#find_package(glm)
#find_package(glew REQUIRED)
#find_package(GLFW REQUIRED)
#find_package(OpenGL REQUIRED)
#find_package(ASSIMP REQUIRED)

include_directories(${ALPHA})

include_directories(${GLEWinclude})
include_directories(${GLFWinclude})
include_directories(${glmInclude})

include_directories(${assimpINCLUDE})

include_directories(${Engine})

include_directories(${Game})
include_directories(${glm})

include_directories(${STB})

set(dll_Files "${PROJECT_SOURCE_DIR}/ALPHA_Engine/.dll")
set(GameModels "${PROJECT_SOURCE_DIR}/ALPHA_Engine/Models")
set(GameTextures "${PROJECT_SOURCE_DIR}/ALPHA_Engine/Textures")
set(GameShaders "${PROJECT_SOURCE_DIR}/ALPHA_Engine/Shaders")
set(EXE_DEST "${PROJECT_BINARY_DIR}/ALPHA_Engine")

# Add source to this project's executable.
add_executable (ALPHA_Engine 
ALPHA_Engine.cpp
ALPHA_Engine.h

${Engine}ModuleList.h
${Engine}BaseConfig.h

${Engine}Core/Host/Host.h
${Engine}Core/Host/Host.cpp
${Engine}Core/World.h
${Engine}Core/World.cpp
${Engine}Core/Object.h
${Engine}Core/Object.cpp
${Engine}Core/Tag.h
${Engine}Core/Tag.cpp

${Engine}Core/Modules/Module.h
${Engine}Core/Modules/Module.cpp

${Engine}Core/Modules/Transform.h
${Engine}Core/Modules/Transform.cpp

${Engine}Core/Math/Vectors.h
${Engine}Core/Math/Vectors.h
${Engine}Core/CoreConfig.h 

${Engine}Graphics_Engine/GraphicsEngineConfig.h
${Engine}Graphics_Engine/Graphics_Engine.h
${Engine}Graphics_Engine/Graphics_Engine.cpp
#${Engine}Graphics_Engine/TextureLoader.h 
#${Engine}Graphics_Engine/TextureLoader.cpp
${Engine}Graphics_Engine/Modules/Camera.h
${Engine}Graphics_Engine/Modules/Camera.cpp
${Engine}Graphics_Engine/Modules/Screen.h
${Engine}Graphics_Engine/Modules/Screen.cpp
 "Engine/EngineConfig.h")

target_link_libraries(ALPHA_Engine 
PRIVATE ${GLFW}/glfw3.lib
PRIVATE ${GLEW}/glew32s.lib
PRIVATE opengl32.lib
PRIVATE ${assimpLIB}assimp-vc143-mtd.lib

)

#target_compile_options(ALPHA_Engine PUBLIC "/Zc:__cplusplus")

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

add_custom_target(copy_textures ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${GameTextures}
	${EXE_DEST}/Textures
	DEPENDS ${dll_Files}
	COMMENT "Copying resources to ${EXE_DEST}/Textures"
)

add_custom_target(copy_shaders ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${GameShaders}
	${EXE_DEST}/Shaders
	DEPENDS ${dll_Files}
	COMMENT "Copying resources to ${EXE_DEST}/Shaders"
)


# TODO: Add tests and install targets if needed.
