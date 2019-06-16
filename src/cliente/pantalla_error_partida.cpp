
#include <SdlTexture.h>
#include <Timer.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include "pantalla_error_partida.h"

PantallaErrorPartida::PantallaErrorPartida(){

}

void PantallaErrorPartida::operator()(){
    const int ancho_pantalla = 800;
    const int alto_pantalla = 600;

    const int FPS = 60;
    const int TICKS_PER_FRAME = 1000/FPS;

    SdlWindow ventana(ancho_pantalla, alto_pantalla);

    //=Fondo=
    std::string ruta_fondo = "assets/inicio5.png";
    SdlTexture textura_fondo(ruta_fondo, ventana);

    bool corriendo = true;


    //=Loop=
    Timer capTimer;
    SDL_Event event;
    while (corriendo){
        ventana.fill(0x33, 0x33, 0x33, 0xFF);

        textura_fondo.render();

        ventana.render();

        while (SDL_PollEvent(&event) != 0){
            switch(event.type) {
                case SDL_QUIT:
                    corriendo = false;
                    break;
            }
        }
        int frameTicks = capTimer.getTicks();

        if (frameTicks < TICKS_PER_FRAME) {
            SDL_Delay(TICKS_PER_FRAME - frameTicks);
        }
    }
}
