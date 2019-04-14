# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../../../ ${CMAKE_CURRENT_SOURCE_DIR}/../../../.bin)

set(CPP_ROOT E:/UEProject/Sword2)


message(CPP_ROOT:____${CPP_ROOT})

include_directories(${CPP_ROOT}/SWord2)
include_directories(${CPP_ROOT}/Engine)

if(WIN32)
    include_directories($${CPP_ROOT}/ThirdParty/Fmod/include)
elseif(ANDROID)
    include_directories(${CPP_ROOT}/ThirdParty/Fmod_Android/include)
endif()

include_directories(${CPP_ROOT}/ThirdParty/SDL2/include)
include_directories(${CPP_ROOT}/ThirdParty/SDL2_image)
include_directories(${CPP_ROOT}/ThirdParty/freetype/include)
include_directories(${CPP_ROOT}/ThirdParty/SDL2_ttf)

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib} )


#add_library(Sword2 SHARED IMPORTED)
#set_target_properties(Sword2
#    PROPERTIES
#    IMPORTED_LOCATION
#    ../../../libs/${ANDROID_ABI}/libSword2.so
#)

target_link_libraries(native-lib
        Sword2)