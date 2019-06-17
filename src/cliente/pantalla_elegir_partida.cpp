
#include <ventana.h>
#include <textura.h>
#include <contador_tiempo.h>
#include <mensajero.h>
#include <protocolo.h>
#include "pantalla_elegir_partida.h"
#include "imagen.h"
#include "boton_jugar.h"
#include "boton_nueva_partida.h"
#include "boton_unirse_a_partida.h"


PantallaElegirPartida::PantallaElegirPartida(std::string puerto,
                                             std::string host,
                                             std::string& puerto_partida):
                                             puerto(puerto_partida),
                                             skt(host, puerto)
                                             {
}


bool PantallaElegirPartida::operator()(){


    // Conexion con servidor.
    skt.conectar();

    Mensajero mensajero_opcion(skt);
    Protocolo protocolo_opcion(mensajero_opcion);

    const int ancho_pantalla = 800;
    const int alto_pantalla = 600;

    const int FPS = 60;
    const int TICKS_PER_FRAME = 1000/FPS;

    Ventana ventana(ancho_pantalla, alto_pantalla);


    //=Fondo=
    std::string ruta_fondo = "assets/inicio5.png";
    Textura textura_fondo(ruta_fondo, ventana);

    bool corriendo = true;

    //=Botones=
    std::string  ruta_botones = "assets/botones_inicio.png";
    Textura botones(ruta_botones, ventana);

    Imagen imagen_nueva_partida(64, 71, 177, 81, &botones); // nueva partida
    BotonNuevaPartida nueva_partida(&imagen_nueva_partida, &corriendo, protocolo_opcion, puerto);
    nueva_partida.colocar((ancho_pantalla / 2) - (177 / 2), (alto_pantalla * 3 / 5) - 40, 177, 81);

    //Falta boton unirse a partida
    Imagen imagen_editar(65, 226, 177, 81, &botones);
    BotonUnirseAPartida unirse_partida(&imagen_editar, &corriendo, protocolo_opcion, puerto);
    unirse_partida.colocar((ancho_pantalla / 2) - (177 / 2), (alto_pantalla * 3 / 5) + 60, 177, 81);


    //=Loop=
    ContadorTiempo capTimer;
    SDL_Event event;
    bool continuar_programa = true;
    while (corriendo){

        ventana.pintar(0x33, 0x33, 0x33, 0xFF);

        nueva_partida.render();
        unirse_partida.render();

        ventana.renderizar();

        while (SDL_PollEvent(&event) != 0){
            switch(event.type) {
                case SDL_MOUSEBUTTONDOWN:{
                    SDL_MouseButtonEvent& mouseEvent = (SDL_MouseButtonEvent&) event;
                    nueva_partida.recibirEvento(mouseEvent);
                    unirse_partida.recibirEvento(mouseEvent);
                    break;
                }
                case SDL_QUIT:
                    corriendo = false;
                    continuar_programa = false;
                    break;
            }
        }
        int frameTicks = capTimer.obtenerTicks();

        if (frameTicks < TICKS_PER_FRAME) {
            SDL_Delay(TICKS_PER_FRAME - frameTicks);
        }
    }

    skt.cerrarCanales();
    skt.cerrarSocket();
    return continuar_programa;
}

