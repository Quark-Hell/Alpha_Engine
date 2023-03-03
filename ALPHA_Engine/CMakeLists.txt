# CMakeList.txt : CMake project for ALPHA_Engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#======================= INCLUSION OF Qt =======================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.4.2/mingw_64/lib/cmake")
set(QT_VERSION 6)

find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

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
 "Engine/Timer.cpp"
 "Engine/Timer.h" 
 "Engine/Alghoritms.h" 
 "Engine/Alghoritms.cpp" 
 "Engine/Material.h"
 "Engine/Material.cpp" 
 "Engine/Texture.cpp" 
 "Engine/Texture.h" 
 "Engine/Vectors.cpp"
 "Engine/Vectors.h"
 "Engine/Matrix.h" 
 "Engine/Matrix.cpp"  
 "Engine/Modules/Geometry.h"
 "Engine/Modules/Geometry.cpp")

target_link_libraries(ALPHA_Engine 
PRIVATE sfml-graphics
PRIVATE sfml-system
PRIVATE sfml-window
PRIVATE ${assimpLIB}assimp-vc143-mtd.lib
PRIVATE Qt6::Core
PRIVATE Qt6::Widgets
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
