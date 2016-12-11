cmake_minimum_required (VERSION 2.8)
project (Towerdefense)

# use C++11 features
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_SOURCE_DIR}/sfml-tmxloader/include)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
add_subdirectory(sfml-tmxloader)
add_executable(Towerdefence src/main.cpp src/menuObjects.cpp src/map.cpp
    src/window.cpp src/enemy.cpp src/game.cpp src/Towers.cpp src/save.cpp)
target_link_libraries(Towerdefence tmx-loader)
