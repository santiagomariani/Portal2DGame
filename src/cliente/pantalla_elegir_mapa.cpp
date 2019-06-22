#include "pantalla_elegir_mapa.h"

PantallaElegirPartida::PantallaElegirMapa(Skt& skt): skt(skt){
}


bool PantallaElegirMapa::operator()(Ventana& ventana){

    Mensajero mensajero_opcion(skt);
    Protocolo protocolo_opcion(mensajero_opcion);

    std::vector<std::string> nombres;
    uint16_t cant = protocolo_opcion.recibirCantidad();
    for (uint16_t i = 0; i < cant; ++i){
        nombres.emplace_back(protocolo_opcion.recibirNombreMapa());
    }

    const int FPS = 60;
    const int TICKS_PER_FRAME = 1000/FPS;

    //=Fondo=
    std::string ruta_fondo = "assets/inicio5.png";
    Textura textura_fondo(ruta_fondo, ventana);
    Imagen imagen_fondo(0, 0, 
                        ventana.obtenerAncho(), 
                        ventana.obtenerAlto(), 
                        &textura_fondo);

    //=Titulo=
    TTF_Init();
    Texto titulo(ventana, 50);
    SDL_Color color = {0, 0, 0}
    titulo.cargarTexto("Elegir mapa", color);

    //=Botones=
    std::string mapa_elegido;
    std::vector<BotonMapa> botones;
    for (auto it=nombres.begin(); it!=nombres.end(); ++it){
        botones.emplace_back(mapa_elegido, *it);
    }

    //=Botonera=
    avergaston;
    Botonera botonera();
    botonera.setBotones(&botones);

    //=Loop=
    ContadorTiempo capTimer;
    SDL_Event event;
    bool continuar_programa = true;
    bool corriendo = true;
    while (corriendo){
        ventana.pintar(0x33, 0x33, 0x33, 0xFF);
        fondo.render();
        titulo.render(destino_titulo);
        nueva_partida.render();
        unirse_partida.render();
        ventana.renderizar();

        while (SDL_PollEvent(&event) != 0) {
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

