cmake_minimum_required(VERSION 3.10)
project(mygame)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

# cpp 'fajli'
add_executable(mygame src/main.cpp src/Player.cpp src/Game.cpp src/Collision.cpp src/Bullet.cpp src/Mouse.cpp src/Layout1.cpp src/Npc.cpp src/Key.cpp)

# Specify the include directory for Square.h
target_include_directories(mygame PRIVATE ${SDL2_INCLUDE_DIRS} include)
target_link_libraries(mygame ${SDL2_LIBRARIES})

# Copy assets folder to build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

#SDL2_IMAGE
include_directories(/usr/include/SDL2)
target_link_libraries(mygame -lSDL2 -lSDL2_image)

