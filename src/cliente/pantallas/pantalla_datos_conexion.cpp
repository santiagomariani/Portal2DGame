#include "pantalla_datos_conexion.h"
#include "ventana.h"
#include "textura.h"
#include <contador_tiempo.h>
#include <SDL2/SDL_ttf.h>
#include "texto.h"
#include "boton_escribir.h"
#include "boton_datos_conexion.h"
#include "imagen.h"
#include "path.h"

PantallaDatosConexion::PantallaDatosConexion(std::string& puerto,
											 std::string& host) :
											 puerto(puerto),
											 host(host){
}


void PantallaDatosConexion::operator()(){
	const int ancho_pantalla = 300;
    const int alto_pantalla = 224;

    const int FPS = 60;
    const int TICKS_PER_FRAME = 1000/FPS;

    std::string assets_path = ASSETS;

    Ventana ventana(ancho_pantalla, alto_pantalla);

    //=Panel=
    std::string ruta_panel = assets_path + "assets/panel_blanco.png";
    Textura textura_panel(ruta_panel, ventana);
    Imagen panel(0, 0, 400, 640, &textura_panel);

    //=Input=
    bool recibir_puerto = false;
    bool recibir_host = false;

    std::string ruta_boton_escribir = assets_path + "assets/boton_escribir.png";
    Textura textura_boton_escribir(ruta_boton_escribir, ventana);
    Imagen imagen_boton_escribir(0, 0, 300, 300, &textura_boton_escribir);
    BotonEscribir escribir_puerto(&imagen_boton_escribir, &recibir_puerto);
    escribir_puerto.colocar(227, 5, 68, 68);
    
    BotonEscribir escribir_host(&imagen_boton_escribir, &recibir_host);
    escribir_host.colocar(227, 78, 68, 68);

    SDL_Rect panel_puerto = {5, 5, 217, 68};
    SDL_Rect panel_host = {5, 78, 217, 68};

    TTF_Init();

    Texto texto_puerto(ventana, 40);
    Texto texto_host(ventana, 40);
    SDL_Color color = {255, 128, 0};

    SDL_StartTextInput();
    //====

    bool corriendo = true;
    //=Boton=
    std::string ruta_boton_datos = assets_path + "assets/boton_mapa.png";
    Textura textura_boton_datos(ruta_boton_datos, ventana);
    Imagen imagen_boton_datos(0, 0, 910, 290, &textura_boton_datos);
    BotonDatosConexion datos(&imagen_boton_datos, &corriendo);
    datos.colocar(5, 151, 290, 68);

    Texto texto_datos(ventana, 40);
    SDL_Color color_datos = {255, 255, 255};
    texto_datos.cargarTexto("Continuar", color_datos);
    //====

    ContadorTiempo capTimer;
    SDL_Event event;
    while (corriendo){
        ventana.pintar(0x47, 0x4B, 0x4E, 0xFF);
        datos.render();
        texto_datos.render(65, 160);
        escribir_puerto.render();
        escribir_host.render();
        if (recibir_puerto){
            panel.render(panel_puerto);
        }
        if (recibir_host){
            panel.render(panel_host);
        }
        if (puerto.length() > 0){
            texto_puerto.cargarTexto(puerto.c_str(), color);
            texto_puerto.render(panel_puerto.x + 10, panel_puerto.y + 7);
        }
        if (host.length() > 0){
            texto_host.cargarTexto(host.c_str(), color);
            texto_host.render(panel_host.x + 10, panel_host.y + 7);
        }
        ventana.renderizar();

        while (SDL_PollEvent(&event) != 0) {
            switch(event.type) {
                case SDL_MOUSEBUTTONDOWN:{
                    SDL_MouseButtonEvent& mouseEvent = (SDL_MouseButtonEvent&) event;
                    escribir_puerto.recibirEvento(mouseEvent);
                    escribir_host.recibirEvento(mouseEvent);
                    datos.recibirEvento(mouseEvent);
                    break;
                }
                case SDL_KEYDOWN:{
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                    if (recibir_puerto){
                        if (keyEvent.keysym.sym == SDLK_BACKSPACE && puerto.length() > 0){
                            puerto.pop_back();
                        }
                    }
                    if (recibir_host){
                        if (keyEvent.keysym.sym == SDLK_BACKSPACE && host.length() > 0){
                            host.pop_back();
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT:
                    if (recibir_puerto && puerto.length() < 5){
                        puerto += event.text.text;
                    }
                    if (recibir_host && host.length() < 16){
                        host += event.text.text;
                    }
                    break;
                case SDL_QUIT:
                    corriendo = false;
                    break;
            }
        }
        int frameTicks = capTimer.obtenerTicks();

        if (frameTicks < TICKS_PER_FRAME) {
            SDL_Delay(TICKS_PER_FRAME - frameTicks);
        }
    }
}