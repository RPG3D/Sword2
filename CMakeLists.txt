
cmake_minimum_required(VERSION 3.6.0)

project(Sword2)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Engine)
include_directories(${PROJECT_SOURCE_DIR}/ThirdParty)

if(WIN32)
	include_directories(${PROJECT_SOURCE_DIR}/ThirdParty/Fmod/include)
elseif(ANDROID)
	include_directories(${PROJECT_SOURCE_DIR}/ThirdParty/Fmod_Android/include)
endif()

include_directories(${PROJECT_SOURCE_DIR}/ThirdParty/SDL2/include)
include_directories(${PROJECT_SOURCE_DIR}/ThirdParty/SDL2_image)
include_directories(${PROJECT_SOURCE_DIR}/ThirdParty/freetype/include)
include_directories(${PROJECT_SOURCE_DIR}/ThirdParty/SDL2_ttf)

add_subdirectory(ThirdParty)
add_subdirectory(Engine)
add_subdirectory(Sword2)