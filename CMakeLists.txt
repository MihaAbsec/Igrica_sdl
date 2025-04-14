cmake_minimum_required(VERSION 3.10)
project(mygame)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

# Find SDL2 and SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)  # <-- Add this line

add_executable(mygame 
    src/main.cpp
    src/Player.cpp
    src/Game.cpp
    src/Collision.cpp
    src/Bullet.cpp
    src/Mouse.cpp
    src/Layout1.cpp
    src/Npc.cpp
    src/Key.cpp
    src/NpcFov.cpp
    src/Camera.cpp
    src/Map.cpp
    src/GameObject.cpp
    src/Menu.cpp
    src/PlayerRadious.cpp
)

# Include directories
target_include_directories(mygame PRIVATE 
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_TTF_INCLUDE_DIRS}  # <-- Add SDL2_ttf includes
    include
)

# Link libraries
target_link_libraries(mygame 
    ${SDL2_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES}  # <-- Link SDL2_ttf
    SDL2_image  # <-- Use CMake target (better than -l flags)
)

# Copy assets and maps
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/maps DESTINATION ${CMAKE_BINARY_DIR})
#GDB LALA 
