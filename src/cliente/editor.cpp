#include "editor.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "ventana.h"
#include "contador_tiempo.h"
#include "imagen.h"
#include "boton_bloque.h"
#include "boton_volver.h"
#include "mapa_editor.h"
#include <vector>
#include "ids.h"
#include "cursor.h"
#include "botonera.h"

#define CELDA 50
#define SEP 40


void Editor::operator()(int* etapa){
	const int ancho_pantalla = 800;
	const int alto_pantalla = 600;

	const int FPS = 60;
	const int TICKS_PER_FRAME = 1000/FPS;
	
	Ventana ventana(ancho_pantalla, alto_pantalla);
	
	//=Imagenes de Bloques=
	std::string ruta_bloques = "assets/blocks.png";
	Textura textura_bloques(ruta_bloques, ventana);
	Imagen bloque_roca(1, 172, 193, 193, &textura_bloques);
	Imagen bloque_metal(1, 600, 193, 193, &textura_bloques);

	std::string ruta_bloques_1 = "assets/blocks1.png";
	Textura textura_bloques_1(ruta_bloques_1, ventana);
	Imagen emisor_arriba_sprite(1, 1242, 193, 193, &textura_bloques_1);
	Imagen emisor_derecha_sprite(1, 1028, 193, 193, &textura_bloques_1);
	Imagen emisor_abajo_sprite(1, 1456, 193, 193, &textura_bloques_1);
	Imagen emisor_izquierda_sprite(1, 814, 193, 193, &textura_bloques_1);

	std::string ruta_boton = "assets/miscellaneous.png";
	Textura textura_misc(ruta_boton, ventana);
	Imagen boton(1, 116, 175, 55, &textura_misc);

	std::string compuertaPath = "assets/gate.png";
	Textura compuertaTexture(compuertaPath, ventana);
	Imagen compuerta_cerrada(1, 21, 193, 385, &compuertaTexture);

	std::string diago_path = "assets/block-diago.png";
	Textura diago_texture(diago_path, ventana);
	Imagen bloqueMetalDiagoSprite(1, 2, 178, 177, &diago_texture);
	std::string diago90_path = "assets/diago-90.png";
	Textura diago90_texture(diago90_path, ventana);
	Imagen bloqueMetalDiago90Sprite(0, 2, 177, 178, &diago90_texture);
	std::string diago180_path = "assets/diago-180.png";
    Textura diago180_texture(diago180_path, ventana);
	Imagen bloqueMetalDiago180Sprite(2, 0, 177, 178, &diago180_texture);
	std::string diago270_path = "assets/diago-270.png";
    Textura diago270_texture(diago270_path, ventana);
	Imagen bloqueMetalDiago270Sprite(2, 0, 177, 178, &diago270_texture);

	std::string ruta_and = "assets/and.png";
    Textura textura_and(ruta_and, ventana);
	Imagen imagen_and(0, 0, 290, 174, &textura_and);

	std::string ruta_or = "assets/or.png";
    Textura textura_or(ruta_or, ventana);
	Imagen imagen_or(0, 0, 466, 299, &textura_or);


	std::map<int, Imagen*> imagenes;
	imagenes.emplace(ID_BLOQUE_ROCA, &bloque_roca);
	imagenes.emplace(ID_BLOQUE_METAL, &bloque_metal);
	imagenes.emplace(ID_BOTON_APAGADO, &boton);
	imagenes.emplace(ID_COMPUERTA_CERRADA, &compuerta_cerrada);
	imagenes.emplace(ID_EMISORARRIBA, &emisor_arriba_sprite);
	imagenes.emplace(ID_EMISORDERECHA, &emisor_derecha_sprite);
	imagenes.emplace(ID_EMISORABAJO, &emisor_abajo_sprite);
	imagenes.emplace(ID_EMISORIZQUIERDA, &emisor_izquierda_sprite);
	imagenes.emplace(ID_BLOQUE_DIAGONAL_0, &bloqueMetalDiagoSprite);
	imagenes.emplace(ID_BLOQUE_DIAGONAL_90, &bloqueMetalDiago90Sprite);
	imagenes.emplace(ID_BLOQUE_DIAGONAL_180, &bloqueMetalDiago180Sprite);
	imagenes.emplace(ID_BLOQUE_DIAGONAL_270, &bloqueMetalDiago270Sprite);
	imagenes.emplace(ID_AND, &imagen_and);
	imagenes.emplace(ID_OR, &imagen_or);
	
	//=Panel=
	std::string ruta_panel = "assets/panel_blanco.png";
    Textura textura_panel(ruta_panel, ventana);
	Imagen panel(0, 0, 400, 640, &textura_panel);

	Cursor cursor(imagenes, ID_BLOQUE_ROCA);
	SDL_Rect actual_espacio = {0, 0, 90, 90};

	//=Botonera=
	Botonera botonera(&panel, ancho_pantalla, alto_pantalla);

	std::vector<BotonBloque> botones_principales;
	botones_principales.emplace_back(cursor, ID_BLOQUE_ROCA, imagenes[ID_BLOQUE_ROCA]);
	botones_principales.emplace_back(cursor, ID_BLOQUE_METAL, imagenes[ID_BLOQUE_METAL]);
	botones_principales.emplace_back(cursor, ID_BOTON_APAGADO, imagenes[ID_BOTON_APAGADO]);
	botones_principales.emplace_back(cursor, ID_COMPUERTA_CERRADA, imagenes[ID_COMPUERTA_CERRADA]);
	botones_principales.emplace_back(cursor, ID_EMISORARRIBA, imagenes[ID_EMISORARRIBA]);
	botones_principales.emplace_back(cursor, ID_EMISORDERECHA, imagenes[ID_EMISORDERECHA]);
	botones_principales.emplace_back(cursor, ID_EMISORABAJO, imagenes[ID_EMISORABAJO]);
	botones_principales.emplace_back(cursor, ID_EMISORIZQUIERDA, imagenes[ID_EMISORIZQUIERDA]);
	botones_principales.emplace_back(cursor, ID_BLOQUE_DIAGONAL_0, imagenes[ID_BLOQUE_DIAGONAL_0]);
	botones_principales.emplace_back(cursor, ID_BLOQUE_DIAGONAL_90, imagenes[ID_BLOQUE_DIAGONAL_90]);
	botones_principales.emplace_back(cursor, ID_BLOQUE_DIAGONAL_180, imagenes[ID_BLOQUE_DIAGONAL_180]);
	botones_principales.emplace_back(cursor, ID_BLOQUE_DIAGONAL_270, imagenes[ID_BLOQUE_DIAGONAL_270]);
	botones_principales.emplace_back(cursor, ID_AND, imagenes[ID_AND]);
	botones_principales.emplace_back(cursor, ID_OR, imagenes[ID_OR]);
	botonera.setBotones(&botones_principales);


	bool corriendo = true;

	//=Botones Opciones=

	std::string ruta_boton_volver = "assets/boton_volver.jpeg";
    Textura textura_boton_volver(ruta_boton_volver, ventana);
	Imagen imagen_boton_volver(0, 0, 255, 255, &textura_boton_volver);
	BotonVolver volver(&imagen_boton_volver, etapa, &corriendo);
	volver.colocar(105, 10, 40, 40);

	SDL_Rect panel_opciones = {95, 0, 120, 70};

	//=Mapa=
	MapaEditor mapa(ancho_pantalla, alto_pantalla, CELDA, cursor);

	ContadorTiempo capTimer;
	SDL_Event event;
	while (corriendo){

		ventana.pintar(0x3F, 0x70, 0x4D, 0x00);

		mapa.render();

		botonera.render();
		panel.render(actual_espacio);
		cursor.render();

		panel.render(panel_opciones);
		volver.render();

		ventana.renderizar();

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
						if (mouseEvent.x > 95 && mouseEvent.x < 215 && mouseEvent.y < 70){
							volver.recibirEvento(mouseEvent);
						}else{
							mapa.recibirEvento(mouseEvent);
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
					*etapa = 3;
					break;
			}
		
		}
		int frameTicks = capTimer.obtenerTicks();

		if (frameTicks < TICKS_PER_FRAME) {
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		}
	}
	//mapa.guardar("prueba.txt");
}
