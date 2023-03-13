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

# Add source to this project's executable.
add_executable (ALPHA_Engine 
mainwindow.cpp
mainwindow.h)

target_link_libraries(ALPHA_Engine 
PRIVATE Qt6::Core
PRIVATE Qt6::Widgets
)

target_compile_options(ALPHA_Engine PUBLIC "/Zc:__cplusplus")