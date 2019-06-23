#include "inicio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <path.h>
#include "ventana.h"
#include "contador_tiempo.h"
#include "fondo_continuo.h"
#include "imagen.h"
#include "boton_jugar.h"
#include "boton_editar.h"

void Inicio::operator()(int* etapa){

	const int ancho_pantalla = 800;
	const int alto_pantalla = 600;

	const int FPS = 60;
	const int TICKS_PER_FRAME = 1000/FPS;
	
	Ventana ventana(ancho_pantalla, alto_pantalla);

	std::string assets_path = ASSETS;

	//=Fondo=
	std::string ruta_fondo = assets_path + "assets/inicio5.png";
	Textura textura_fondo(ruta_fondo, ventana);
	
	FondoContinuo fondo(1800, 1100, ancho_pantalla, alto_pantalla, 3, textura_fondo);
	//=Titulo=
	std::string  ruta_titulo = assets_path + "assets/titulo.png";
    Textura titulo_textura(ruta_titulo, ventana);
	Imagen titulo(0, 0, 470, 200, &titulo_textura);
	SDL_Rect destino_titulo = {(ancho_pantalla / 2) - (470 / 2), (alto_pantalla / 3) - 100, 470, 200};
	
	bool corriendo = true;

	//=Botones=
	std::string  ruta_botones = assets_path + "assets/botones_inicio.png";
    Textura botones(ruta_botones, ventana);
	Imagen imagen_jugar(64, 71, 177, 81, &botones);

	BotonJugar jugar(&imagen_jugar, etapa, &corriendo);
	jugar.colocar((ancho_pantalla / 2) - (177 / 2),
			(alto_pantalla * 3 / 5) - 40, 177, 81);

	Imagen imagen_editar(65, 226, 177, 81, &botones);
	BotonEditar editar(&imagen_editar, etapa, &corriendo);
	editar.colocar((ancho_pantalla / 2) - (177 / 2),
			(alto_pantalla * 3 / 5) + 60, 177, 81);

	//=Loop=
	ContadorTiempo capTimer;
	SDL_Event event;
	while (corriendo){

		ventana.pintar(0x33, 0x33, 0x33, 0xFF);
		fondo.render();
		titulo.render(destino_titulo);

		jugar.render();
		editar.render();

		ventana.renderizar();

		while (SDL_PollEvent(&event) != 0){
			switch(event.type) {
				case SDL_MOUSEBUTTONDOWN:{
					SDL_MouseButtonEvent& mouseEvent = (SDL_MouseButtonEvent&) event;
					jugar.recibirEvento(mouseEvent);
					editar.recibirEvento(mouseEvent);
					break;
				}
				case SDL_QUIT:
					corriendo = false;
					*etapa = 3;
					break;
			}
		}
		int frameTicks = capTimer.obtenerTicks();

		if (frameTicks < TICKS_PER_FRAME) {
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		}
	}
}
