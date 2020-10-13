cmake_minimum_required(VERSION 2.8)
project(WaterSimulation)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -lmingw32 -lSDL2main -lSDL2")

aux_source_directory(. DIR_SRCS)

include_directories("C:/x86_64-w64-mingw32/include/SDL2")
link_directories("C:/x86_64-w64-mingw32/lib")
link_directories("C:/x86_64-w64-mingw32/bin")
add_executable(WaterSimulation ${DIR_SRCS} main.cpp)

target_link_libraries(WaterSimulation SDL2.dll)
