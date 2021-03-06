#include "editor.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ventana.h"
#include "contador_tiempo.h"
#include "imagen.h"
#include "boton_bloque.h"
#include "boton_volver.h"
#include "boton_guardar.h"
#include "boton_escribir.h"
#include "mapa_editor.h"
#include <vector>
#include "ids.h"
#include "cursor.h"
#include "botonera.h"
#include "texto.h"

#include <iostream>
#include <path.h>
#include "yaml-cpp/yaml.h"

#define CELDA 50
#define SEP 40


void Editor::operator()(int* etapa){
	std::string assets_path = ASSETS;

	const int ancho_pantalla = 800;
	const int alto_pantalla = 600;

	const int FPS = 60;
	const int TICKS_PER_FRAME = 1000/FPS;
	
	Ventana ventana(ancho_pantalla, alto_pantalla);
	
	//=Imagenes de Bloques=
	std::string ruta_bloques = assets_path + "assets/blocks.png";
	Textura textura_bloques(ruta_bloques, ventana);
	Imagen bloque_roca(1, 172, 193, 193, &textura_bloques);
	Imagen bloque_metal(1, 600, 193, 193, &textura_bloques);

	std::string ruta_bloques_1 = assets_path + "assets/blocks1.png";
	Textura textura_bloques_1(ruta_bloques_1, ventana);
	Imagen emisor_arriba_sprite(1, 1242, 193, 193, &textura_bloques_1);
	Imagen emisor_derecha_sprite(1, 1028, 193, 193, &textura_bloques_1);
	Imagen emisor_abajo_sprite(1, 1456, 193, 193, &textura_bloques_1);
	Imagen emisor_izquierda_sprite(1, 814, 193, 193, &textura_bloques_1);

	Imagen receptor_arriba_sprite(233, 1243, 192, 192, &textura_bloques_1);
	Imagen receptor_derecha_sprite(235, 1029, 192, 192, &textura_bloques_1);
	Imagen receptor_abajo_sprite(232, 1457, 192, 192, &textura_bloques_1);
	Imagen receptor_izquierda_sprite(235, 814, 192, 192, &textura_bloques_1);

	std::string ruta_boton = assets_path + "assets/miscellaneous.png";
	Textura textura_misc(ruta_boton, ventana);
	Imagen boton(1, 116, 175, 55, &textura_misc);

	std::string compuertaPath = assets_path + "assets/gate.png";
	Textura compuertaTexture(compuertaPath, ventana);
	Imagen compuerta_cerrada(1, 21, 193, 385, &compuertaTexture);

	Imagen acido(1, 1545, 300, 61, &textura_misc);

	Imagen barra_energia(528, 689, 8, 220, &textura_misc);

	std::string diago_path = assets_path + "assets/block-diago.png";
	Textura diago_texture(diago_path, ventana);
	Imagen bloqueMetalDiagoSprite(1, 2, 178, 177, &diago_texture);
	std::string diago90_path = assets_path + "assets/diago-90.png";
	Textura diago90_texture(diago90_path, ventana);
	Imagen bloqueMetalDiago90Sprite(0, 2, 177, 178, &diago90_texture);
	std::string diago180_path = assets_path + "assets/diago-180.png";
    Textura diago180_texture(diago180_path, ventana);
	Imagen bloqueMetalDiago180Sprite(2, 0, 177, 178, &diago180_texture);
	std::string diago270_path = assets_path + "assets/diago-270.png";
    Textura diago270_texture(diago270_path, ventana);
	Imagen bloqueMetalDiago270Sprite(2, 0, 177, 178, &diago270_texture);

	std::string ruta_sp = assets_path + "assets/spawn_point.png";
	Textura textura_sp(ruta_sp, ventana);
	Imagen imagen_sp(0, 0, 300, 300, &textura_sp);

	std::string ruta_and = assets_path + "assets/and.png";
    Textura textura_and(ruta_and, ventana);
	Imagen imagen_and(0, 0, 290, 174, &textura_and);

	std::string ruta_or = assets_path + "assets/or.png";
    Textura textura_or(ruta_or, ventana);
	Imagen imagen_or(0, 0, 466, 299, &textura_or);

	std::string ruta_torta = assets_path + "assets/torta.png";
	Textura textura_torta(ruta_torta, ventana);
	Imagen imagen_torta(0, 0, 381, 389, &textura_torta);

	std::string ruta_roca = assets_path + "assets/fx.png";
	Textura textura_roca(ruta_roca, ventana);
	Imagen imagen_roca(1, 4513, 83, 83, &textura_roca);

	std::map<int, Imagen*> imagenes;
	imagenes.emplace(ID_BLOQUE_ROCA, &bloque_roca);
	imagenes.emplace(ID_BLOQUE_METAL, &bloque_metal);
	imagenes.emplace(ID_BOTON_APAGADO, &boton);
	imagenes.emplace(ID_COMPUERTA_CERRADA, &compuerta_cerrada);
	imagenes.emplace(ID_EMISORARRIBA, &emisor_arriba_sprite);
	imagenes.emplace(ID_EMISORDERECHA, &emisor_derecha_sprite);
	imagenes.emplace(ID_EMISORABAJO, &emisor_abajo_sprite);
	imagenes.emplace(ID_EMISORIZQUIERDA, &emisor_izquierda_sprite);
	imagenes.emplace(ID_RECEPTORARRIBA_DESACTIVADO, &receptor_arriba_sprite);
	imagenes.emplace(ID_RECEPTORABAJO_DESACTIVADO, &receptor_abajo_sprite);
	imagenes.emplace(ID_RECEPTORIZQUIERDA_DESACTIVADO, &receptor_izquierda_sprite);
	imagenes.emplace(ID_RECEPTORDERECHA_DESACTIVADO, &receptor_derecha_sprite);
	imagenes.emplace(ID_BLOQUE_DIAGONAL_0, &bloqueMetalDiagoSprite);
	imagenes.emplace(ID_BLOQUE_DIAGONAL_90, &bloqueMetalDiago90Sprite);
	imagenes.emplace(ID_BLOQUE_DIAGONAL_180, &bloqueMetalDiago180Sprite);
	imagenes.emplace(ID_BLOQUE_DIAGONAL_270, &bloqueMetalDiago270Sprite);
	imagenes.emplace(ID_ACIDO, &acido);
	imagenes.emplace(ID_BARRAENERGIA, &barra_energia);
	imagenes.emplace(ID_SPAWNPOINT, &imagen_sp);
	imagenes.emplace(ID_AND, &imagen_and);
	imagenes.emplace(ID_OR, &imagen_or);
	imagenes.emplace(ID_TORTA, &imagen_torta);
	imagenes.emplace(ID_ROCA, &imagen_roca);

	//=Panel=
	std::string ruta_panel = assets_path + "assets/panel_blanco.png";
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
	botones_principales.emplace_back(cursor, ID_ROCA, imagenes[ID_ROCA]);
	botones_principales.emplace_back(cursor, ID_RECEPTORDERECHA_DESACTIVADO, imagenes[ID_RECEPTORDERECHA_DESACTIVADO]);
	botones_principales.emplace_back(cursor, ID_RECEPTORIZQUIERDA_DESACTIVADO, imagenes[ID_RECEPTORIZQUIERDA_DESACTIVADO]);
	botones_principales.emplace_back(cursor, ID_RECEPTORABAJO_DESACTIVADO, imagenes[ID_RECEPTORABAJO_DESACTIVADO]);
	botones_principales.emplace_back(cursor, ID_RECEPTORARRIBA_DESACTIVADO, imagenes[ID_RECEPTORARRIBA_DESACTIVADO]);
	botones_principales.emplace_back(cursor, ID_BLOQUE_DIAGONAL_0, imagenes[ID_BLOQUE_DIAGONAL_0]);
	botones_principales.emplace_back(cursor, ID_BLOQUE_DIAGONAL_90, imagenes[ID_BLOQUE_DIAGONAL_90]);
	botones_principales.emplace_back(cursor, ID_BLOQUE_DIAGONAL_180, imagenes[ID_BLOQUE_DIAGONAL_180]);
	botones_principales.emplace_back(cursor, ID_BLOQUE_DIAGONAL_270, imagenes[ID_BLOQUE_DIAGONAL_270]);
	botones_principales.emplace_back(cursor, ID_ACIDO, imagenes[ID_ACIDO]);
	botones_principales.emplace_back(cursor, ID_BARRAENERGIA, imagenes[ID_BARRAENERGIA]);
	botones_principales.emplace_back(cursor, ID_SPAWNPOINT, imagenes[ID_SPAWNPOINT]);
	botones_principales.emplace_back(cursor, ID_AND, imagenes[ID_AND]);
	botones_principales.emplace_back(cursor, ID_OR, imagenes[ID_OR]);
	botones_principales.emplace_back(cursor, ID_TORTA, imagenes[ID_TORTA]);
	botonera.setBotones(&botones_principales);


	//=Mapa=
	MapaEditor mapa(ancho_pantalla, alto_pantalla, CELDA, cursor);
	bool corriendo = true;
	bool recibir_texto = false;

	//=Botones Opciones=

	std::string nombre_mapa = "Nombre Mapa";
	std::string ruta_boton_escribir = assets_path + "assets/boton_escribir.png";
	Textura textura_boton_escribir(ruta_boton_escribir, ventana);
	Imagen imagen_boton_escribir(0, 0, 300, 300, &textura_boton_escribir);
	BotonEscribir escribir(&imagen_boton_escribir, &recibir_texto);
	escribir.colocar(ancho_pantalla - (ancho_pantalla / 6) - 50, 5, 40, 40);

	SDL_Rect panel_input = {195, 0, ancho_pantalla - (ancho_pantalla / 6) - 320, 50};

	std::string ruta_boton_volver = assets_path + "assets/boton_volver.jpeg";
    Textura textura_boton_volver(ruta_boton_volver, ventana);
	Imagen imagen_boton_volver(0, 0, 255, 255, &textura_boton_volver);
	BotonVolver volver(&imagen_boton_volver, etapa, &corriendo);
	volver.colocar(100, 5, 40, 40);

	std::string ruta_boton_guardar = assets_path + "assets/boton_guardar.jpeg";
	Textura textura_boton_guardar(ruta_boton_guardar, ventana);
	Imagen imagen_boton_guardar(0, 0, 255, 255, &textura_boton_guardar);
	BotonGuardar guardar(&imagen_boton_guardar, mapa, nombre_mapa);
	guardar.colocar(145, 5, 40, 40);

	SDL_Rect panel_opciones = {95, 0, 95, 50};


	TTF_Init();

	Texto texto(ventana, 30);
	SDL_Color color = {0, 0, 0};

	SDL_StartTextInput();

	//=Loop=

	ContadorTiempo capTimer;
	SDL_Event event;
	while (corriendo){

		ventana.pintar(0x3F, 0x70, 0x4D, 0x00);

		mapa.render();

		botonera.render();
		panel.render(actual_espacio);
		cursor.render();
		escribir.render();

		if (recibir_texto){
			panel.render(panel_input);
		}

		if (nombre_mapa.length() > 0){
			texto.cargarTexto(nombre_mapa.c_str(), color);
			texto.render(200, 5);
		}

		panel.render(panel_opciones);
		volver.render();
		guardar.render();

		ventana.renderizar();

		while (SDL_PollEvent(&event) != 0){
			switch(event.type) {
				case SDL_KEYDOWN:{
						SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
						if (!recibir_texto){
							mapa.recibirEvento(keyEvent);
						} else {
							if (keyEvent.keysym.sym == SDLK_BACKSPACE && nombre_mapa.length() > 0){
								nombre_mapa.pop_back();
							}
						}
						break;
				}
				case SDL_TEXTINPUT:
					if (recibir_texto && nombre_mapa.length() < 20){
						nombre_mapa += event.text.text;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:{
					SDL_MouseButtonEvent& mouseEvent = (SDL_MouseButtonEvent&) event;
					if (!(botonera.colisiona(mouseEvent.x, mouseEvent.y))){
						if (mouseEvent.y < 50){
							escribir.recibirEvento(mouseEvent);
							volver.recibirEvento(mouseEvent);
							guardar.recibirEvento(mouseEvent);
						} else {
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
	TTF_Quit();
}
