
cmake_minimum_required(VERSION 3.6.0)

project(Lua C)

FILE(GLOB ALL_HEADER_SRCS ./*.h)

FILE(GLOB ALL_CPP_SRCS ./*.c)

add_library(Lua STATIC ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS})