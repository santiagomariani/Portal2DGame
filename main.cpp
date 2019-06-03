#include <iostream>
#include "Box2D/Box2D.h"

#include "disparo.h"
#include "BloqueRoca.h"
#include "BloqueMetal.h"
#include "chell.h"
#include "mundo.h"
#include "estado_teclado.h"
#include "personajes.h"
#include "cuerpo.h"
#include "SdlWindow.h"
#include "ViewChell.h"
#include "contact_listener.h"
#include "Timer.h"
#include "Camera.h"
#include "CoordConverter.h"
#include "portal.h"
#include "boton.h"
#include "estado_logico.h"
#include "compuerta.h"
#include "ids.h"
#include "or.h"
#include "and.h"
#include "Roca.h"
#include "BolaEnergia.h"
#include "EmisorArriba.h"

#include <thread>
#include <pthread.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

#define CONVERSION 100
#define PI 3.14159265



#include "editor.h"
#include "EmisorAbajo.h"
#include "EmisorDerecha.h"
#include "EmisorIzquierda.h"
#include "ReceptorArriba.h"
#include "ReceptorAbajo.h"
#include "ReceptorDerecha.h"
#include "ReceptorIzquierda.h"


int main() {

//=====================Pruebas De Ariel===================
	Editor e;
	e();
//========================================================

	b2Vec2 gravity(0.0f, -9.8f);
	Mundo world(gravity);
	ContactListener listener;
	world.setContactListener(listener);

	Personajes personajes(world);

	b2Vec2 pos_piedra(-6,-2);
	BloqueRoca rocaPiedra(ID_BLOQUE_ROCA, world, pos_piedra);

	b2Vec2 pos_roca(-8, 0);
	Roca roca(world, pos_roca);

	b2Vec2 pos_roca2(-6, 0);
	Roca roca2(world, pos_roca2);

	std::vector<BloqueMetal> bloques;
	b2Vec2 pos(-40, -3);
	b2Vec2 inc(1, 0);
	for (int j = 0; j < 45; ++j){
		BloqueMetal bloque(ID_BLOQUE_METAL, world, pos);
		bloques.push_back(std::move(bloque));
		pos += inc;
	}

	std::vector<BloqueMetal> pared;
	b2Vec2 pos_bloque(2, -3);
	b2Vec2 inc_pared(0, 1);
	for (int j = 0; j < 2; ++j){
		BloqueMetal roca3(ID_BLOQUE_METAL, world, pos_bloque);
		pared.push_back(std::move(roca3));
		pos_bloque += inc_pared;
	}
	pos_bloque.Set(2, 2);
	BloqueMetal bloque_en_el_aire(ID_BLOQUE_METAL, world, pos_bloque);

	// Receptores
	b2Vec2 pos_receptor(-17, -2);
	ReceptorArriba receptor_arriba(world, pos_receptor);
	pos_receptor.Set(-16, 2);
	ReceptorAbajo receptor_abajo(world, pos_receptor);
    pos_receptor.Set(-15, 1);
    ReceptorDerecha receptor_derecha(world, pos_receptor);
    pos_receptor.Set(-18, 1);
    ReceptorIzquierda receptor_izquierda(world, pos_receptor);

	b2Vec2 pos_boton(0, -2.35);
	Boton b(pos_boton, world);
	b2Vec2 pos_boton2(-4, -2.35);
	Boton b2(pos_boton2, world);

	EstadoLogico* estado_boton = new EstadoLogico(b); //usar unique pointer?
	EstadoLogico* estado_boton2 = new EstadoLogico(b2);

	// con botones OR:
	/*Or compuerta_or;
	compuerta_or.agregar(estado_boton);
	compuerta_or.agregar(estado_boton2);

	b2Vec2 pos_compuerta(-1, -2);
	Compuerta comp(pos_compuerta, world, compuerta_or);*/

	// con botones AND:
	And compuerta_and;
	compuerta_and.agregar(estado_boton);
	compuerta_and.agregar(estado_boton2);

	b2Vec2 pos_compuerta(-1, -1.5);
	Compuerta comp(pos_compuerta, world, compuerta_and);

	int id = personajes.agregar_chell();

	// Emisores
	b2Vec2 pos_emisor(-16, -2);
	EmisorArriba emisor_arriba(world, pos_emisor);
	pos_emisor.Set(-17, 2);
	EmisorAbajo emisor_abajo(world, pos_emisor);
	pos_emisor.Set(-22, 1);
	EmisorDerecha emisor_derecha(world, pos_emisor);
	pos_emisor.Set(-11, 1);
	EmisorIzquierda emisor_izquierda(world, pos_emisor);

	// b2Vec2 bola_energia_pos(-2, -1);
	// b2Vec2 bola_energia_dir(1, 0);
	// BolaEnergia bola_energia(world, bola_energia_pos, bola_energia_dir);

//======================================SDL======================================

	const int screenWidth = 800;
	const int screenHeight = 600;

	const int FPS = 60;
	const int TICKS_PER_FRAME = 1000/FPS;


	SdlWindow window(screenWidth, screenHeight);

	std::string bgPath = "assets/industrial-background.jpg";
	SdlTexture background(bgPath, window);

	Camera camera(screenWidth, screenHeight, background);

	// window.fill(0x33, 0x33, 0x33, 0xFF);

	// Disparo
	std::string fxPath = "assets/fx.png";
	SdlTexture fxTexture(fxPath, window);
	Sprite disparoSprite(111, 59, 1, 1920, 3, fxTexture);

	// Bloques roca y metal
	std::string blocksPath = "assets/blocks1.png";
	SdlTexture blocksTexture(blocksPath, window);
	Sprite bloqueSprite(193, 193, 1, 172, 1, blocksTexture);
	Sprite bloqueMetalSprite(193, 193, 1, 600, 1, blocksTexture);

	// Boton apagado y prendidos
	std::string botonPath = "assets/miscellaneous.png";
	SdlTexture botonTexture(botonPath, window);
	Sprite botonSprite(175, 55, 1, 116, 1, botonTexture);
	Sprite botonPrendidoSprite(175, 74, 1, 192, 1, botonTexture);

	// Compuerta cerrada y abierta
	std::string compuertaPath = "assets/gate.png";
	SdlTexture compuertaTexture(compuertaPath, window);
	Sprite compuertaCerradaSprite(193, 385, 1, 21, 1, compuertaTexture);
	Sprite compuertaAbiertaSprite(193, 385, 1553, 2437, 1, compuertaTexture);
	Sprite compuertaAbriendoSprite(193, 385, 1, 2051, 19, compuertaTexture);

	//Portal azul
	std::string portalAzulPath = "assets/portAzul.png";
	SdlTexture portalAzulTexture(portalAzulPath, window);
	Sprite portalAzulSprite(193, 193, 0, 0, 1, portalAzulTexture);

	//Portal naranja
	std::string portalNaranjaPath = "assets/portNaranja.png";
	SdlTexture portalNaranjaTexture(portalNaranjaPath, window);
	Sprite portalNaranjaSprite(193, 193, 0, 0, 1, portalNaranjaTexture);

	// Piedra
	Sprite piedra_sprite1(85, 83, 1, 4513, 1, fxTexture);
	Sprite piedra_sprite2(85, 83, 87, 4513, 1, fxTexture);
	Sprite piedra_sprite3(85, 83, 173, 4513, 1, fxTexture);
	Sprite piedra_sprite4(85, 83, 259, 4513, 1, fxTexture);
	Sprite piedra_sprite5(85, 83, 345, 4513, 1, fxTexture);
	Sprite piedra_sprite6(85, 83, 431, 4513, 1, fxTexture);
	Sprite piedra_sprite7(85, 83, 517, 4513, 1, fxTexture);
	Sprite piedra_sprite8(85, 83, 603, 4513, 1, fxTexture);

	// Bola de energia.
	Sprite bola_energia_sprite(171, 119, 1, 2000, 5, fxTexture);

	// EmisorArriba
	Sprite emisor_arriba_sprite(193, 193, 1, 1242, 1, blocksTexture);
	// EmisorDerecha
	Sprite emisor_derecha_sprite(193, 193, 1, 1028, 1, blocksTexture);
	// EmisorAbajo
	Sprite emisor_abajo_sprite(193, 193, 1, 1456, 1, blocksTexture);
	// EmisorIzquierda
	Sprite emisor_izquierda_sprite(193, 193, 1, 814, 1, blocksTexture);

	// Receptores

	// ReceptorArriba
	// 	Activado
	Sprite receptor_arriba_activado_sprite(192, 192, 466, 1243, 1, blocksTexture);
	// Desactivado
	Sprite receptor_arriba_desactivado_sprite(192, 192, 233, 1243, 1, blocksTexture);

	// ReceptorDerecha
	// 	Activado
	Sprite receptor_derecha_activado_sprite(192, 192, 465, 1029, 1, blocksTexture);
	// Desactivado
	Sprite receptor_derecha_desactivado_sprite(192, 192, 235, 1029, 1, blocksTexture);

	// ReceptorIzquierda
	// 	Activado
	Sprite receptor_izquierda_activado_sprite(192, 192, 464, 814, 1, blocksTexture);
	// Desactivado
	Sprite receptor_izquierda_desactivado_sprite(192, 192, 235, 814, 1, blocksTexture);

	// ReceptorAbajo
	// 	Activado
	Sprite receptor_abajo_activado_sprite(192, 192, 468, 1457, 1, blocksTexture);
	// Desactivado
	Sprite receptor_abajo_desactivado_sprite(192, 192, 232, 1457, 1, blocksTexture);

	ViewChell viewChell(window);

	std::map<int, Renderable*> texturas;
	texturas[ID_CHELL] = &viewChell;
	texturas[ID_BLOQUE_ROCA] = &bloqueSprite;
	texturas[ID_DISPARO] = &disparoSprite;
	texturas[ID_BLOQUE_METAL] = &bloqueMetalSprite;
	texturas[ID_PORTAL_AZUL] = &portalAzulSprite;
	texturas[ID_PORTAL_NARANJA] = &portalNaranjaSprite;
	texturas[ID_BOTON_APAGADO] = &botonSprite;
	texturas[ID_COMPUERTA_CERRADA] = &compuertaCerradaSprite;
	texturas[ID_COMPUERTA_ABRIENDO] = &compuertaAbriendoSprite;
	texturas[ID_COMPUERTA_ABIERTA] = &compuertaAbiertaSprite;
	texturas[ID_ROCA] = &piedra_sprite1;
	texturas[ID_BOTON_PRENDIDO] = &botonPrendidoSprite;
	texturas[ID_EMISORARRIBA] = &emisor_arriba_sprite;
	texturas[ID_EMISORDERECHA] = &emisor_derecha_sprite;
	texturas[ID_EMISORABAJO] = &emisor_abajo_sprite;
	texturas[ID_EMISORIZQUIERDA] = &emisor_izquierda_sprite;
	texturas[ID_BOLAENERGIA] = &bola_energia_sprite;
	texturas[ID_RECEPTORARRIBA_ACTIVADO] = &receptor_arriba_activado_sprite;
	texturas[ID_RECEPTORARRIBA_DESACTIVADO] = &receptor_arriba_desactivado_sprite;
	texturas[ID_RECEPTORDERECHA_ACTIVADO] = &receptor_derecha_activado_sprite;
	texturas[ID_RECEPTORDERECHA_DESACTIVADO] = &receptor_derecha_desactivado_sprite;
	texturas[ID_RECEPTORABAJO_ACTIVADO] = &receptor_abajo_activado_sprite;
	texturas[ID_RECEPTORABAJO_DESACTIVADO] = &receptor_abajo_desactivado_sprite;
	texturas[ID_RECEPTORIZQUIERDA_ACTIVADO] = &receptor_izquierda_activado_sprite;
	texturas[ID_RECEPTORIZQUIERDA_DESACTIVADO] = &receptor_izquierda_desactivado_sprite;

	CoordConverter coordConverter(screenWidth, screenHeight);
//======================================Loop======================================


	bool running = true;
	EstadoTeclado teclado;

	Timer fpsTimer;
	Timer capTimer;

	int countedFrames = 1;

	while (running) {
		fpsTimer.start();
		SDL_Event event;
		window.fill(0x33, 0x33, 0x33, 0xFF);
		Chell& chell = personajes.obtener_chell(id);
		SDL_Rect destChell = coordConverter.box2DToSDL(chell);
		camera.renderBg();
		camera.updateCamera(destChell);
		b2Body *cuerpos = world.obtenerBodies();
		while (cuerpos){
			Cuerpo *actual = (Cuerpo*)cuerpos->GetUserData();
			if (!actual){
				cuerpos = cuerpos->GetNext();
				continue;
			}
			SDL_Rect dest = coordConverter.box2DToSDL(*actual);
			int id = actual->getId();
			if (id == ID_DISPARO) {
				camera.render(*texturas[id], dest, (((Disparo*)actual)->getAngle()) * 180/PI * -1);
			} else if (id == ID_PORTAL_AZUL || id == ID_PORTAL_NARANJA){
				camera.render(*texturas[id], dest, (((Portal*)actual)->getAnguloSalida()) * 180/PI *-1);
			} else if (id == ID_BOLAENERGIA) {
				camera.render(*texturas[id], dest, (((BolaEnergia*)actual)->getAngle()) * 180/PI * -1);
			} else {
				camera.render(*texturas[id], dest);
			}
			cuerpos = cuerpos->GetNext();
		}

		while (SDL_PollEvent(&event) != 0){
			switch(event.type) {
				case SDL_KEYDOWN:{
						SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
						teclado.agregar_evento(keyEvent);
						break;
				}
				case SDL_KEYUP:{
						SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
						teclado.agregar_evento(keyEvent);
						break;
				}
				case SDL_MOUSEBUTTONDOWN:{
					SDL_MouseButtonEvent& mouseEvent = (SDL_MouseButtonEvent&) event;
					if ((mouseEvent.button) == SDL_BUTTON_LEFT){
						b2Vec2 click = coordConverter.sdlToBox2D(mouseEvent.x, mouseEvent.y, camera);
						chell.dispararAzul(click);
					}
					if ((mouseEvent.button) == SDL_BUTTON_RIGHT){
						b2Vec2 click = coordConverter.sdlToBox2D(mouseEvent.x, mouseEvent.y, camera);
						chell.dispararNaranja(click);
					}
					break;
				}
				case SDL_QUIT:
					running = false;
					break;
			}
		
		}
		chell.agarrarRoca(teclado);
		chell.mover(teclado);
		world.actualizar();
		window.render();
		

		// Solo para ver cantidad de FPS en terminal.
		//float avgFPS = (countedFrames / (fpsTimer.getTicks() / 1000.f));
		//if (avgFPS > 2000000) {
		//	avgFPS = 0;
		//}
		//std::cout << "FPS: " << avgFPS << std::endl;
		//++countedFrames;
		

		int frameTicks = capTimer.getTicks();

		if (frameTicks < TICKS_PER_FRAME) {
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		}
	}

	return 0;
}

