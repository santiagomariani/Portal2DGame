cmake_minimum_required(VERSION 3.14)
project(untitled)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

add_executable(untitled main.cpp SdlWindow.cpp SdlTexture.cpp SdlException.cpp Sprite.cpp Timer.cpp ViewChell.cpp Renderable.cpp Camera.cpp)

# ${CMAKE_CURRENT_SOURCE_DIR}

find_package(Threads REQUIRED)

message("[INFO] Adding '${CMAKE_SOURCE_DIR}/libs' as include directory")
include_directories(${CMAKE_SOURCE_DIR}/libs)

message("[INFO] Adding Box2D as library")
file(GLOB_RECURSE BOX2D_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libs/Box2D/*.cpp" "libs/Box2D/*.h")

add_library(Box2D STATIC ${BOX2D_SOURCES} BloqueRoca.h BloqueRoca.cpp disparo.h disparo.cpp main.cpp chell.h chell.cpp estado_teclado.cpp personajes.cpp mundo.cpp cuerpo.h contact_listener.cpp CoordConverter.cpp Bloque.cpp Bloque.h BloqueMetal.cpp BloqueMetal.h pistola.h pistola.cpp portal.cpp Camera.cpp Teletransportador.cpp Teletransportador.h boton.h boton.cpp compuerta_logica.h or.h or.cpp and.h and.cpp compuerta.cpp compuerta.h estado_logico.cpp estado_logico.h estado_compuerta.h estado_abierta.h estado_abierta.cpp estado_cerrada.cpp estado_cerrada.h estado_abriendo.cpp estado_cerrando.h estado_cerrando.cpp estado_abriendo.h)

target_link_libraries(untitled Box2D ${CMAKE_THREAD_LIBS_INIT} SDL2 SDL2_image)
