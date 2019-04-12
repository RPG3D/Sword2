
cmake_minimum_required(VERSION 3.6.0)

FILE(GLOB ALL_HEADER_SRCS ${PROJECT_SOURCE_DIR}/Engine/*.h ${PROJECT_SOURCE_DIR}/Engine/*/*.h)

FILE(GLOB ALL_CPP_SRCS ${PROJECT_SOURCE_DIR}/Engine/*.cpp ${PROJECT_SOURCE_DIR}/Engine/*/*.cpp)

#Android use iconv
if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    include_directories(D:/AndroidSDK/ndk-bundle/sources/android/support/include)
    #link_libraries(D:/AndroidSDK/ndk-bundle/sources/cxx-stl/llvm-libc++/libs/${ANDROID_ABI}/libandroid_support.a)
endif()

add_definitions("-D_DRAW_FPS")

add_library(Engine STATIC ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS} )