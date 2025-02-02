cmake_minimum_required(VERSION 3.10)
project(mygame)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

# Add Square.cpp to the list of source files
add_executable(mygame src/main.cpp src/Square.cpp src/Line.cpp src/Detection.cpp)

# Specify the include directory for Square.h
target_include_directories(mygame PRIVATE ${SDL2_INCLUDE_DIRS} include)
target_link_libraries(mygame ${SDL2_LIBRARIES})
