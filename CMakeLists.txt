cmake_minimum_required(VERSION 3.19)
INCLUDE(FindPkgConfig)
project(jumpjump)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++17 -O0")
set(CMAKE_CXX_STANDARD 17)

add_executable(
    jumpjump
    src/main.cpp
    src/TextureManager.cpp
    src/ECSManager.cpp
    src/PhysicsEngine.cpp
    src/OnScreenDebugger.cpp
    src/LevelManager.cpp
)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})