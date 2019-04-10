

##### general #####
cmake_minimum_required(VERSION 3.10.0)
project(SDL_image C)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)


FILE(GLOB ALL_HEADER_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

FILE(GLOB ALL_CPP_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c)



##### library generation #####
add_library(SDL2_image ${ALL_HEADER_SRCS} ${ALL_CPP_SRCS})
target_link_libraries(SDL2_image SDL2 )

