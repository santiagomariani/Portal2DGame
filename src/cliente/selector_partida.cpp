#include "selector_partida.h"
#include "mensajero.h"
#include "textura.h"
#include "texto.h"
#include "protocolo.h"
#include "imagen.h"
#include "contador_tiempo.h"
#include "boton_mapa.h"
#include "botonera_mapas.h"
#include "boton_aceptar_partida.h"
#include <vector>
#include <iostream>

SelectorPartida::SelectorPartida(Protocolo& protocolo):
                                         protocolo(protocolo){
}


bool SelectorPartida::operator()(Ventana& ventana, std::string& puerto){
    int ancho_v = ventana.obtenerAncho();
    int alto_v = ventana.obtenerAlto();

    std::vector<std::string> partidas;

    uint16_t cant = protocolo.recibirCantidad();
    for (uint16_t i = 0; i < cant; ++i){
        partidas.emplace_back(protocolo.recibirPuerto());
    }

    const int FPS = 60;
    const int TICKS_PER_FRAME = 1000/FPS;

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
    titulo.cargarTexto("Elegir Partida", color);

    //=Botones=
    std::string ruta_imagen_boton = "assets/boton_mapa.png";
    Textura textura_boton_mapa(ruta_imagen_boton, ventana);
    Imagen imagen_boton(0, 0, 910, 290, &textura_boton_mapa);
    
    std::string partida_elegida;
    std::vector<BotonMapa> botones;
    for (auto it=partidas.begin(); it!=partidas.end(); ++it){
        botones.emplace_back(&imagen_boton, partida_elegida, *it, ventana);
    }

    //=Botonera=
    std::string ruta_panel = "assets/panel_blanco.png";
    Textura textura_panel(ruta_panel, ventana);
    Imagen imagen_panel(0, 0, 400, 640, &textura_panel);

    int ancho_bot = ancho_v / 2;
    int alto_bot = (alto_v * 2) / 3;
    SDL_Rect destino_botonera = {ancho_v / 2 - ancho_bot / 2,
                                 alto_v / 6, ancho_bot, alto_bot};

    BotoneraMapas botonera(&imagen_panel, destino_botonera);
    botonera.setBotones(&botones);

    Texto actual(ventana, 30);
    SDL_Color color_actual = {255, 255, 0};

    // para loop y boton aceptar:
    bool corriendo = true;
    //=Boton aceptar=
    BotonAceptarPartida aceptar(&imagen_boton, &corriendo, ventana, partida_elegida, puerto);
    aceptar.colocar(340, 32, 115, 50);

    //=Loop=
    ContadorTiempo capTimer;
    SDL_Event event;
    bool continuar_programa = true;
    while (corriendo){
        imagen_fondo.render(dest_fondo);
        titulo.render(0, 0);
        aceptar.render();
        if (partida_elegida.length() > 0){
            actual.cargarTexto(partida_elegida, color_actual);
            actual.render(10, (alto_v*6)/7);
        }
        botonera.render();
        ventana.renderizar();
        while (SDL_PollEvent(&event) != 0) {
            switch(event.type) {
                case SDL_MOUSEBUTTONDOWN:{
                    SDL_MouseButtonEvent& mouseEvent = (SDL_MouseButtonEvent&) event;
                    if (botonera.colisiona(mouseEvent.x, mouseEvent.y)){
                        botonera.recibirEvento(mouseEvent);
                    }
                    aceptar.recibirEvento(mouseEvent);
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
    return continuar_programa;
}