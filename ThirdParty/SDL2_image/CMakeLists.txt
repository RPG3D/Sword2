

##### general #####
cmake_minimum_required(VERSION 3.6.0)
project(SDL_image C)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)


FILE(GLOB ALL_HEADER_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

FILE(GLOB ALL_CPP_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_definitions("-DLOAD_BMP")
add_definitions("-DLOAD_PNG")


set(ZLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../zlib)

set(SKIP_INSTALL_LIBRARIES true)
set(SKIP_INSTALL_ALL true)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../zlib)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/libpng)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/libpng)


##### library generation #####
add_library(SDL2_image STATIC ${ALL_HEADER_SRCS} ${ALL_CPP_SRCS})
target_link_libraries(SDL2_image SDL2 )

