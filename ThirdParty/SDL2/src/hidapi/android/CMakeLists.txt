

cmake_minimum_required(VERSION 3.6.0)


add_library(hidapi SHARED hid.cpp)


find_library( # Sets the name of the path variable.
    log-lib

    # Specifies the name of the NDK library that
    # you want CMake to locate.
    log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
    hidapi

    # Links the target library to the log library
    # included in the NDK.
    ${log-lib} )
