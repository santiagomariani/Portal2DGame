cmake_minimum_required(VERSION 3.14)
project(untitled)

#modo debug
#Agregar la opción -DDEBUG cuando se quiera correr el programa localmente
#

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -std=c++11 -Wall -pedantic -pthread -ggdb -DDEBUG")


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

file(GLOB CLIENT_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/cliente" "src/cliente/editor" "src/cliente/hilos" "src/cliente/graficos" "src/cliente/grabacion" "src/cliente/pantallas" "src/cliente/sonidos")
include_directories(${CLIENT_HEADERS})

add_executable(portal_cliente ${CLIENT_SOURCES}  ${CLIENT_LIB_SOURCES})

target_link_libraries(portal_cliente SDL2 SDL2_image SDL2_mixer SDL2_ttf Box2D avformat avcodec avutil swscale ${CMAKE_THREAD_LIBS_INIT} yaml-cpp)

message("[INFO] Loading sources to the server")
file(GLOB_RECURSE SERVER_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/servidor/*.cpp" "src/servidor/*.h")
file(GLOB SERVER_LIBS_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/comun/*.h" "src/comun/*.cpp")

file(GLOB SERVER_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/servidor" "src/servidor/modelo_juego" "src/servidor/hilos")
include_directories(${SERVER_HEADERS})

add_executable(portal_servidor ${SERVER_SOURCES} ${SERVER_LIBS_SOURCES})

target_link_libraries(portal_servidor Box2D SDL2 avformat avcodec avutil swscale ${CMAKE_THREAD_LIBS_INIT} yaml-cpp)

######################################
# Esto es por si se usa el modo debug
file(COPY assets DESTINATION ./)
file(COPY mapas DESTINATION ./)
file(COPY config.yaml DESTINATION ./)
#######################################

#message("[INFO] Adding Installation directives")
#INSTALL(TARGETS portal_cliente portal_servidor DESTINATION /usr/bin)
#INSTALL(DIRECTORY assets DESTINATION /var/Portal)
#INSTALL(DIRECTORY mapas DESTINATION /var/Portal)
#INSTALL(FILES config.yaml DESTINATION /etc/Portal)
