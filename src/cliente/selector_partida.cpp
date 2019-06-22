#include "selector_partida.h"
#include "mensajero.h"
#include "textura.h"
#include "texto.h"
#include "protocolo.h"
#include "imagen.h"
#include "contador_tiempo.h"
#include "boton_mapa.h"
#include "botonera_mapas.h"
#include <vector>
#include <iostream>

SelectorPartida::SelectorPartida(Protocolo& protocolo):
                                         protocolo(protocolo){
}


bool SelectorPartida::operator()(Ventana& ventana){

    std::vector<int> partidas;
    partidas.push_back(0);
    partidas.push_back(1);
    partidas.push_back(2);
    partidas.push_back(3);

    /*uint16_t cant = protocolo.recibirCantidad();
    for (uint16_t i = 0; i < cant; ++i){
        partidas.emplace_back(protocolo.recibirPartida());
    }*/

    const int FPS = 60;
    const int TICKS_PER_FRAME = 1000/FPS;

    //=Fondo=
    std::string ruta_fondo = "assets/inicio5.png";
    Textura textura_fondo(ruta_fondo, ventana);
    Imagen imagen_fondo(0, 0, 
                        1800, 
                        1100, 
                        &textura_fondo);

    SDL_Rect dest_fondo = {0, 0, 
                           ventana.obtenerAncho(), 
                           ventana.obtenerAlto()};

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
        botones.emplace_back(&imagen_boton, partida_elegida, std::to_string(*it), ventana);
    }

    //=Botonera=
    std::string ruta_panel = "assets/panel_blanco.png";
    Textura textura_panel(ruta_panel, ventana);
    Imagen imagen_panel(0, 0, 400, 640, &textura_panel);

    SDL_Rect destino_botonera = {ventana.obtenerAncho()/2 - 400, 
                                ventana.obtenerAlto()/4, 
                                300, 800};

    BotoneraMapas botonera(&imagen_panel, destino_botonera);
    botonera.setBotones(&botones);

    //=Loop=
    ContadorTiempo capTimer;
    SDL_Event event;
    bool continuar_programa = true;
    bool corriendo = true;
    while (corriendo){
        imagen_fondo.render(dest_fondo);
        titulo.render(0, 0);
        botonera.render();
        ventana.renderizar();
        while (SDL_PollEvent(&event) != 0) {
            switch(event.type) {
                case SDL_MOUSEBUTTONDOWN:{
                    SDL_MouseButtonEvent& mouseEvent = (SDL_MouseButtonEvent&) event;
                    if (botonera.colisiona(mouseEvent.x, mouseEvent.y)){
                        botonera.recibirEvento(mouseEvent);
                    }
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