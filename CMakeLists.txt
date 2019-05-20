cmake_minimum_required(VERSION 3.14)
project(untitled)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

add_executable(untitled main.cpp SdlWindow.cpp SdlTexture.cpp SdlException.cpp Sprite.cpp Timer.cpp ViewChell.cpp)

# ${CMAKE_CURRENT_SOURCE_DIR}

find_package(Threads REQUIRED)

message("[INFO] Adding '${CMAKE_SOURCE_DIR}/libs' as include directory")
include_directories(${CMAKE_SOURCE_DIR}/libs)

message("[INFO] Adding Box2D as library")
file(GLOB_RECURSE BOX2D_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libs/Box2D/*.cpp" "libs/Box2D/*.h")
add_library(Box2D STATIC ${BOX2D_SOURCES} roca.h roca.cpp disparo.h disparo.cpp main.cpp chell.h chell.cpp estado_teclado.cpp personajes.cpp mundo.cpp cuerpo.h)

target_link_libraries(untitled Box2D ${CMAKE_THREAD_LIBS_INIT} SDL2 SDL2_image)
