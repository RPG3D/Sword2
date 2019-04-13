
cmake_minimum_required(VERSION 3.6.0)


FILE(GLOB ALL_HEADER_SRCS ${PROJECT_SOURCE_DIR}/Sword2/*.h ${PROJECT_SOURCE_DIR}/Sword2/*/*.h)

FILE(GLOB ALL_CPP_SRCS ${PROJECT_SOURCE_DIR}/Sword2/*.cpp ${PROJECT_SOURCE_DIR}/Sword2/*/*.cpp)


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Engine)
include_directories(${PROJECT_SOURCE_DIR}/ThirdParty/Lua)

if(WIN32)

    link_directories(

        ${PROJECT_SOURCE_DIR}/ThirdParty/Fmod/lib/x64
        #${PROJECT_SOURCE_DIR}/ThirdParty/Ffmpeg/lib
        
        ${PROJECT_BINARY_DIR}/ThirdParty/SDL2/Debug

        ${PROJECT_BINARY_DIR}/ThirdParty/Lua/Debug

        ${PROJECT_SOURCE_DIR}/ThirdParty/SDL2_image/Debug
        ${PROJECT_SOURCE_DIR}/ThirdParty/SDL2_ttf/Debug
        ${PROJECT_SOURCE_DIR}/build/ThirdParty/freetype/Debug
        ${PROJECT_SOURCE_DIR}/build/ThirdParty/zlib/Debug
        ${PROJECT_SOURCE_DIR}/build/ThirdParty/SDL_image/libpng-1.6.32/Debug
    )

    #windows lib
    link_libraries(Winmm)
    link_libraries(Mincore)
    link_libraries(Version)
    link_libraries(User32)
    link_libraries(Imm32)

    #dmod lib
    link_libraries(fmod_vc)
    link_libraries(fmodL_vc)
    
    link_libraries(SDL2-staticd)
    link_libraries(zlibstaticd)
    link_libraries(png_static)

elseif(ANDROID)

    link_directories(

        ${PROJECT_BINARY_DIR}/ThirdParty/Lua

        ${PROJECT_BINARY_DIR}/ThirdParty/SDL2_image
        ${PROJECT_BINARY_DIR}/ThirdParty/SDL2_ttf
        ${PROJECT_BINARY_DIR}/ThirdParty/freetype
        ${PROJECT_BINARY_DIR}/ThirdParty/SDL_image/external/libpng-1.6.32d
    )

    link_libraries(SDL2)
    link_libraries(z)
    link_libraries(png_static)

    #dmod lib
    #link_libraries(fmod)
    #link_libraries(fmodL)

endif()

link_libraries(Lua)

link_libraries(SDL2_image)
link_libraries(SDL2_ttf)


#game engine lib
link_libraries(Engine)

if(WIN32)
    add_executable(Sword2 ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS} )
elseif(ANDROID)  
    add_library(Sword2 SHARED ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS} ) 
endif()