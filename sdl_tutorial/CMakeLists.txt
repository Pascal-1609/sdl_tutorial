cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(sdl_tutorial ${SOURCES})

target_include_directories(sdl_tutorial PRIVATE sdl2main)
target_include_directories(sdl_tutorial PRIVATE sdl2_image)
target_include_directories(sdl_tutorial PRIVATE sdl2_mixer)
target_include_directories(sdl_tutorial PRIVATE sdl2_ttf)

