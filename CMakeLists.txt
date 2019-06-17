cmake_minimum_required(VERSION 3.14)
project(untitled)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -std=c++11 -Wall -pedantic -pthread -ggdb")

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS_RELEASE "-O0")

# add_executable(untitled main.cpp Ventana.cpp Textura.cpp Textura.h SdlException.cpp Sprite.cpp ContadorTiempo.cpp VistaChell.cpp Renderizable.cpp Roca.cpp)


#add_subdirectory(${CMAKE_SOURCE_DIR} /libs/yaml-cpp)

message("[INFO] Adding '${CMAKE_SOURCE_DIR}/libs' as include directory")
include_directories(${CMAKE_SOURCE_DIR}/libs)


message("[INFO] Adding '${CMAKE_SOURCE_DIR}/src/comun' as include directory")
include_directories(${CMAKE_SOURCE_DIR}/src/comun)



message("[INFO] Adding Box2D as library")
file(GLOB_RECURSE BOX2D_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libs/Box2D/*.cpp" "libs/Box2D/*.h")

add_library(Box2D STATIC ${BOX2D_SOURCES})


message("[INFO] Loading sources to the client")
file(GLOB_RECURSE CLIENT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/cliente/*.cpp" "src/cliente/*.h")
file(GLOB CLIENT_LIB_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/comun/*.h" "src/comun/*.cpp")

add_executable(portal_cliente ${CLIENT_SOURCES}  ${CLIENT_LIB_SOURCES})
target_link_libraries(portal_cliente SDL2 SDL2_image SDL2_mixer Box2D ${CMAKE_THREAD_LIBS_INIT})

message("[INFO] Loading sources to the server")
file(GLOB_RECURSE SERVER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/servidor/*.cpp" "src/servidor/*.h")
file(GLOB SERVER_LIBS_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/comun/*.h" "src/comun/*.cpp")

add_executable(portal_servidor ${SERVER_SOURCES} ${SERVER_LIBS_SOURCES})
target_link_libraries(portal_servidor Box2D SDL2 SDL2_image SDL2_mixer ${CMAKE_THREAD_LIBS_INIT})
