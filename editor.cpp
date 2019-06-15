#include "editor.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "Ventana.h"
#include "Timer.h"
#include "fondo_continuo.h"
#include "imagen.h"
#include "boton_jugar.h"
#include "boton_editar.h"
#include "boton_bloque.h"
#include "mapa_editor.h"
#include <vector>
#include "ids.h"
#include "cursor.h"
#include "botonera.h"

#define CELDA 50
#define SEP 40

#include <iostream>

void Editor::operator()(){
	const int ancho_pantalla = 800;
	const int alto_pantalla = 600;

	const int FPS = 60;
	const int TICKS_PER_FRAME = 1000/FPS;
	
	SdlWindow ventana(ancho_pantalla, alto_pantalla);
	/*
	//=Imagenes de Bloques=

	std::string ruta_bloques = "assets/blocks.png";
	SdlTexture textura_bloques(ruta_bloques, ventana);
	Imagen bloque_roca(1, 172, 193, 193, &textura_bloques);
	Imagen bloque_metal(1, 600, 193, 193, &textura_bloques);


	std::map<int, Imagen*> imagenes;
	imagenes.emplace(ID_BLOQUE_ROCA, &bloque_roca);
	imagenes.emplace(ID_BLOQUE_METAL, &bloque_metal);
	
	//=Panel=
	std::string ruta_panel = "assets/panel_blanco.png";
	SdlTexture textura_panel(ruta_panel, ventana);
	Imagen panel(0, 0, 400, 640, &textura_panel);

	Cursor cursor(ID_BLOQUE_ROCA, CELDA, CELDA);
	SDL_Rect actual_espacio = {0, 0, CELDA + SEP, CELDA + SEP};
	SDL_Rect actual = {SEP / 2, SEP / 2, CELDA, CELDA};

	//=Botonera=
	Botonera botonera(imagenes, cursor, &panel, ancho_pantalla, alto_pantalla, CELDA);
	
	//=Mapa=
	MapaEditor mapa(imagenes, ancho_pantalla, alto_pantalla, CELDA);
*/
	Timer capTimer;
	SDL_Event event;
	bool corriendo = true;/*
	while (corriendo){

		ventana.fill(0x3F, 0x70, 0x4D, 0x00);

		mapa.render();

		botonera.render();
		panel.render(actual_espacio);
		imagenes[cursor.id]->render(actual);

		ventana.render();

		while (SDL_PollEvent(&event) != 0){
			switch(event.type) {
				case SDL_KEYDOWN:{
						SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
						mapa.recibirEvento(keyEvent);
						break;
				}
				case SDL_MOUSEBUTTONDOWN:{
					SDL_MouseButtonEvent& mouseEvent = (SDL_MouseButtonEvent&) event;
					if (!(botonera.colisiona(mouseEvent.x, mouseEvent.y))){
						if (mouseEvent.button == SDL_BUTTON_LEFT){
							mapa.agregar(cursor.id, mouseEvent.x, mouseEvent.y, cursor.ancho, cursor.alto);
						} else if (mouseEvent.button == SDL_BUTTON_RIGHT){
							mapa.quitar(mouseEvent.x, mouseEvent.y);
						}
					} else {
						botonera.recibirEvento(mouseEvent);
					}
					break;
				}
				case SDL_MOUSEWHEEL:{
					SDL_MouseWheelEvent& mouseEvent = (SDL_MouseWheelEvent&) event;
					int mouse_x;
					int mouse_y;
					SDL_GetMouseState(&mouse_x, &mouse_y);
					if (botonera.colisiona(mouse_x, mouse_y)){
						botonera.recibirEvento(mouseEvent);
					}
					break;
				}
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
*/
	//=Fondo=
	std::string ruta_fondo = "assets/inicio5.png";
	SdlTexture textura_fondo(ruta_fondo, ventana);
	
	FondoContinuo fondo(1800, 1100, ancho_pantalla, alto_pantalla, 3, textura_fondo);
	//=Titulo=
	std::string  ruta_titulo = "assets/titulo.png";
	SdlTexture titulo_textura(ruta_titulo, ventana);
	Imagen titulo(0, 0, 470, 200, &titulo_textura);
	SDL_Rect destino_titulo = {(ancho_pantalla / 2) - (470 / 2), (alto_pantalla / 3) - 100, 470, 200};

	//=Botones=
	std::string  ruta_botones = "assets/botones_inicio.png";
	SdlTexture botones(ruta_botones, ventana);
	Imagen imagen_jugar(64, 71, 177, 81, &botones);

	BotonJugar jugar(&imagen_jugar);
	jugar.colocar((ancho_pantalla / 2) - (177 / 2), (alto_pantalla * 3 / 5) - 40, 177, 81);

	Imagen imagen_editar(65, 226, 177, 81, &botones);
	BotonEditar editar(&imagen_editar);
	editar.colocar((ancho_pantalla / 2) - (177 / 2), (alto_pantalla * 3 / 5) + 60, 177, 81);

	//=Loop=
	corriendo = true;
	while (corriendo){

		ventana.fill(0x33, 0x33, 0x33, 0xFF);
		fondo.render();
		titulo.render(destino_titulo);

		jugar.render();
		editar.render();

		ventana.render();

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
					break;
			}
		
		}
		int frameTicks = capTimer.getTicks();

		if (frameTicks < TICKS_PER_FRAME) {
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		}
	}
}
