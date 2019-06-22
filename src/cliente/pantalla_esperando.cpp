#include "pantalla_esperando.h"

#include "textura.h"
#include "texto.h"
#include "protocolo.h"
#include "imagen.h"
#include "th_esperando_id_partida.h"
#include <iostream>

PantallaEsperando::PantallaEsperando(){
}


int PantallaEsperando::operator()(Protocolo& protocolo, Skt& skt){
    Ventana ventana(800, 600);
    int ancho_v = ventana.obtenerAncho();
    int alto_v = ventana.obtenerAlto();

    //=Fondo=
    std::string ruta_fondo = "assets/inicio5.png";
    Textura textura_fondo(ruta_fondo, ventana);
    Imagen imagen_fondo(0, 0, 
                        1800, 
                        1100, 
                        &textura_fondo);

    SDL_Rect dest_fondo = {0, 0, ancho_v, alto_v};

    //=Titulo=
    TTF_Init();
    Texto titulo(ventana, 50);
    SDL_Color color = {0, 0, 0};
    titulo.cargarTexto("Esperando Jugadores...", color);

    //=Loop=
    SDL_Event event;
    imagen_fondo.render(dest_fondo);
    titulo.render(0, 0);
    ventana.renderizar();

    int id;
    ThEsperarIdPartida recibir_id(protocolo, skt, &id);
    recibir_id.start();
    bool continuar = true;
    bool cancelar = false;
    while (continuar){
        while (SDL_PollEvent(&event) != 0) {
            switch(event.type) { 
                case SDL_QUIT:
                    continuar = false;
                    recibir_id.terminar();
                    cancelar = true;
                    break;
            }
        }
        if (recibir_id.terminado()){
            break;
        }
    }
    recibir_id.join();
    if (cancelar){
        return -1;
    }
    return id;
}