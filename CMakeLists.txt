cmake_minimum_required(VERSION 3.29)
project(voxel_engine_metal)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/VoxelApp.cpp
    src/VoxelApp.h
    src/Renderer.cpp
    src/Renderer.h
    src/main.cpp
        src/World.cpp
        src/World.h
        src/Camera.cpp
        src/Camera.h
        src/utils/Math.h
        src/Chunk.cpp
        src/Chunk.h
        src/Voxel.cpp
        src/Voxel.h
)

include_directories(include)
include_directories(src)

add_subdirectory(metal-cmake)

add_executable(voxel_engine_metal ${SOURCES})

target_link_libraries(voxel_engine_metal METAL_CPP)