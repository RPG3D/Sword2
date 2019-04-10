
cmake_minimum_required(VERSION 3.10.0)

FILE(GLOB ALL_HEADER_SRCS ${PROJECT_SOURCE_DIR}/Engine/*.h ${PROJECT_SOURCE_DIR}/Engine/*/*.h)

FILE(GLOB ALL_CPP_SRCS ${PROJECT_SOURCE_DIR}/Engine/*.cpp ${PROJECT_SOURCE_DIR}/Engine/*/*.cpp)

add_definitions("-D_DRAW_FPS")

add_library(Engine STATIC ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS} )