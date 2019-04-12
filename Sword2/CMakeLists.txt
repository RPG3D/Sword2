
cmake_minimum_required(VERSION 3.6.0)


FILE(GLOB ALL_HEADER_SRCS ${PROJECT_SOURCE_DIR}/Sword2/*.h ${PROJECT_SOURCE_DIR}/Sword2/*/*.h)

FILE(GLOB ALL_CPP_SRCS ${PROJECT_SOURCE_DIR}/Sword2/*.cpp ${PROJECT_SOURCE_DIR}/Sword2/*/*.cpp)


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Engine)
include_directories(${PROJECT_SOURCE_DIR}/ThirdParty/Lua)


link_directories(

    ${PROJECT_SOURCE_DIR}/ThirdParty/Fmod/lib/x64
    ${PROJECT_SOURCE_DIR}/ThirdParty/Ffmpeg/lib
    
    ${PROJECT_BINARY_DIR}/ThirdParty/SDL2/Debug

    ${PROJECT_BINARY_DIR}/ThirdParty/Lua/Debug

    ${PROJECT_SOURCE_DIR}/ThirdParty/SDL2_image/Debug
    ${PROJECT_SOURCE_DIR}/ThirdParty/SDL2_ttf/Debug
    ${PROJECT_SOURCE_DIR}/build/ThirdParty/freetype/Debug
    ${PROJECT_SOURCE_DIR}/build/ThirdParty/zlib/Debug
    ${PROJECT_SOURCE_DIR}/build/ThirdParty/SDL_image/libpng-1.6.32/Debug

)

link_libraries(lua)

link_libraries(SDL2-staticd)
link_libraries(SDL2_image)
link_libraries(SDL2_ttf)

link_libraries(png_static)

link_libraries(zlibstaticd)

#ffmpeg lib
link_libraries(avcodec)
link_libraries(avdevice)
link_libraries(avfilter)
link_libraries(avformat)
link_libraries(avutil)
link_libraries(swresample)
link_libraries(swscale)

#dmod lib
link_libraries(fmod_vc)
link_libraries(fmodL_vc)

#windows lib
link_libraries(Winmm)
link_libraries(Mincore)
link_libraries(Version)
link_libraries(User32)
link_libraries(Imm32)


#game engine lib
link_libraries(Engine)

add_executable(Sword2 ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS} )