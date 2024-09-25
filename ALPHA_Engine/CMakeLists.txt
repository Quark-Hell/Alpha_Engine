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

set(Game_DEST "${PROJECT_SOURCE_DIR}/Game/Game/ALPHA_Engine")

# Add source to this project's executable.
add_library (ALPHA_Engine SHARED
ALPHA_Engine.cpp
ALPHA_Engine.h

${Engine}ModuleList.h
${Engine}BaseConfig.h
${Engine}EngineConfig.h

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

${Engine}UserScriptsRegister/UserScriptConfig.h
${Engine}UserScriptsRegister/Registry.h
${Engine}UserScriptsRegister/Registry.cpp
${Engine}UserScriptsRegister/UserScript.h
${Engine}UserScriptsRegister/UserScript.cpp
)

target_link_libraries(ALPHA_Engine 
PRIVATE ${GLFW}/glfw3.lib
PRIVATE ${GLEW}/glew32s.lib
PRIVATE opengl32.lib
PRIVATE ${assimpLIB}assimp-vc143-mtd.lib

)

#target_compile_options(ALPHA_Engine PUBLIC "/Zc:__cplusplus")

#copy files in engine build
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
#copy files in engine build

#copy files in game build
add_custom_command(TARGET ALPHA_Engine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory 
	${Game_DEST}/dll
	COMMAND ${CMAKE_COMMAND} -E copy
	${EXE_DEST}/ALPHA_Engine.dll
	${Game_DEST}/dll/ALPHA_Engine.dll
)

add_custom_target(copy_dll_game ALL 
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${dll_Files}
	${Game_DEST}/dll
	COMMENT "Copying resources to ${Game_DEST}"
)

add_custom_target(copy_shaders_game ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${GameShaders}
	${Game_DEST}/shaders
	COMMENT "Copying resources to ${Game_DEST}/shaders"
)

add_custom_target(copy_textures_game ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${GameTextures}
	${Game_DEST}/textures
	COMMENT "Copying resources to ${Game_DEST}/textures"
)

add_custom_target(copy_models_game ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${GameModels}
	${Game_DEST}/models
	COMMENT "Copying resources to ${Game_DEST}/models"
)
#copy files in game build

# TODO: Add tests and install targets if needed.
