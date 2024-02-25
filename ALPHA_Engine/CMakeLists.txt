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

SET(STB "${PROJECT_SOURCE_DIR}/ALPHA_Engine/STB/")

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
${assimpINCLUDE}assimp/Importer.hpp
${assimpINCLUDE}assimp/scene.h
${assimpINCLUDE}assimp/postprocess.h

${Game}GameModels.h 
${Game}GameModels.cpp 

${Engine}Binds.h
${Engine}Binds.cpp

${Engine}Alghoritms.h
${Engine}Alghoritms.cpp
${Engine}Basical_Type.h
${Engine}Basical_Type.cpp
${Engine}Collision.h
${Engine}Collision.cpp
${Engine}Graphic_Engine.h
${Engine}Graphic_Engine.cpp
"Engine/Modules/Material.h"
"Engine/Modules/Material.cpp"

${Engine}Object.h 
${Engine}Object.cpp   
${Engine}Texture.h 
${Engine}Texture.cpp
${Engine}Timer.h
${Engine}Timer.cpp
${Engine}Vectors.h
${Engine}Vectors.cpp
${Engine}World.h  
${Engine}World.cpp 

${Engine}Modules/Camera.h
${Engine}Modules/Camera.cpp
${Engine}Modules/Geometry.h
${Engine}Modules/Geometry.cpp
${Engine}Modules/Mesh.h
${Engine}Modules/Mesh.cpp
${Engine}Modules/Module.h
${Engine}Modules/Module.cpp
${Engine}Modules/Physics.h
${Engine}Modules/Physics.cpp
"Engine/AdditionalMath.h" 
"Engine/AdditionalMath.cpp" 
"Engine/Modules/BoxCollider.h"
"Engine/Modules/BoxCollider.cpp" 
${glm}glm.hpp 
 "Engine/Modules/MeshCollider.h"
 "Engine/Modules/MeshCollider.cpp"
 "Engine/Modules/Transform.h"
 "Engine/Modules/Transform.cpp"
 "Engine/Plane.h" 
  
 
 "Engine/BVH_Tree.h" 
 "Engine/BVH_Tree.cpp" 
 "Engine/AABB.h" 
 "Engine/AABB.cpp"
 "Engine/Modules/Collider.h" 
 "Engine/Modules/Collider.cpp" 
 "Engine/Modules/MovableModule.h" 
 "Engine/Modules/MovableModule.cpp"  
 "Engine/ShadersProgram/ShaderProgram.h" 
 "Engine/ShadersProgram/ShaderProgram.cpp"
 "Engine/Modules/Light/Light.h" 
 "Engine/Modules/Light/Light.cpp" 
 "Engine/Modules/Light/DirectLight.h"
 "Engine/Modules/Light/DirectLight.cpp"
 "Engine/Modules/Light/PointLight.h" 
 "Engine/Modules/Light/PointLight.cpp"
 "Engine/Modules/Light/SpotLight.h" 
 "Engine/Modules/Light/SpotLight.cpp"
 "Engine/Modules/DebugMesh.h"
 "Engine/Modules/DebugMesh.cpp"  "Engine/ShadersProgram/OpaqueShader.h" "Engine/ShadersProgram/OpaqueShader.cpp" "Engine/ShadersProgram/ColliderWireframeShader.h" "Engine/ShadersProgram/ColliderWireframeShader.cpp"  "Engine/ShadersProgram/CubeMapShader.h" "Engine/ShadersProgram/CubeMapShader.cpp" "Engine/ShadersProgram/PathShader.h" "Engine/ShadersProgram/PathShader.cpp" "Engine/TextureLoader.h" "Engine/TextureLoader.cpp")

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
