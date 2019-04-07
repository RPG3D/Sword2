
cmake_minimum_required(VERSION 3.10.0)


FILE(GLOB ALL_HEADER_SRCS ${PROJECT_SOURCE_DIR}/Sword2/*.h ${PROJECT_SOURCE_DIR}/Sword2/*/*.h)

FILE(GLOB ALL_CPP_SRCS ${PROJECT_SOURCE_DIR}/Sword2/*.cpp ${PROJECT_SOURCE_DIR}/Sword2/*/*.cpp)


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Engine)
include_directories(${PROJECT_SOURCE_DIR}/ThirdParty/Lua/include)


link_directories(
    ${PROJECT_SOURCE_DIR}/ThirdParty/SDL2/lib
    ${PROJECT_SOURCE_DIR}/ThirdParty/Ffmpeg/lib
    ${PROJECT_SOURCE_DIR}/ThirdParty/Lua/lib
    ${PROJECT_SOURCE_DIR}/ThirdParty/Fmod/lib/x64
    ${PROJECT_SOURCE_DIR}/ThirdParty/SDL2_image/lib/x64
    ${PROJECT_SOURCE_DIR}/ThirdParty/SDL2_ttf/lib/x64

)

link_libraries(lua.lib)
link_libraries(SDL2.lib)
link_libraries(SDL2_image.lib)
link_libraries(SDL2_ttf.lib)

link_libraries(avcodec.lib)
link_libraries(avdevice.lib)
link_libraries(avfilter.lib)
link_libraries(avformat)
link_libraries(avutil)
link_libraries(swresample)
link_libraries(swscale)
link_libraries(fmod_vc)
link_libraries(fmodL_vc)

link_libraries(Winmm)
link_libraries(Mincore)
link_libraries(User32)
link_libraries(Imm32)



link_libraries(Engine)


add_executable(Sword2 ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS} )