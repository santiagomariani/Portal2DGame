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
#include "ids.h"

#include <thread>
#include <pthread.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

#define CONVERSION 100
#define PI 3.14159265



int main() {

	b2Vec2 gravity(0.0f, -9.8f);
	Mundo world(gravity);
	ContactListener listener;
	world.setContactListener(listener);

	Personajes personajes(world);

	std::vector<BloqueRoca> rocas;
	b2Vec2 pos(-40, -3);
	b2Vec2 inc(1, 0);
	for (int j = 0; j < 40; ++j){
		BloqueRoca roca(ID_ROCA, world, pos);
		rocas.push_back(std::move(roca));
		pos += inc;
	}

	pos.Set(0, -2);
	BloqueMetal roca(ID_METAL, world, pos);
	//rocas.push_back(std::move(roca));
	pos.Set(0, 1);
	//BloqueRoca roca2(ID_ROCA, world, pos);
	//rocas.push_back(std::move(roca2));

	std::vector<BloqueRoca> pared;
	b2Vec2 pos_roca(2, -3);
	b2Vec2 inc_pared(0, 1);
	for (int j = 0; j < 5; ++j){
		BloqueRoca roca3(ID_ROCA, world, pos_roca);
		pared.push_back(std::move(roca3));
		pos_roca += inc_pared;
	}
	//Portal portal();
	//Cliente 0
	int id = personajes.agregar_chell();


//======================================SDL======================================

	const int screenWidth = 800;
	const int screenHeight = 600;

	const int FPS = 60;
	const int TICKS_PER_FRAME = 1000/FPS;

	Camera camera(screenWidth, screenHeight);

	SdlWindow window(screenWidth, screenHeight);
	window.fill(0x33, 0x33, 0x33, 0xFF);

	// Disparo
	std::string fxPath = "assets/fx.png";
	SdlTexture fxTexture(fxPath, window);
	Sprite disparoSprite(111, 59, 1, 1920, 3, fxTexture);

	// Bloque
	std::string blocksPath = "assets/blocks.png";
	SdlTexture blocksTexture(blocksPath, window);
	Sprite bloqueSprite(193, 193, 1, 172, 1, blocksTexture);
	Sprite bloqueMetalSprite(193, 193, 1, 600, 1, blocksTexture);

	//Portal
	std::string portalPath = "assets/portAzul.png";
	SdlTexture portalTexture(portalPath, window);
	Sprite portalSprite(193, 193, 0, 0, 1, portalTexture);

	ViewChell viewChell(window);

	std::map<int, Renderable*> texturas;
	texturas[ID_CHELL] = &viewChell;
	texturas[ID_ROCA] = &bloqueSprite;
	texturas[ID_DISPARO] = &disparoSprite;
	texturas[ID_METAL] = &bloqueMetalSprite;
	texturas[ID_PORTAL_AZUL] = &portalSprite;

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
		camera.updateCamera(destChell);
		b2Body *cuerpos = world.obtenerBodies();
		while (cuerpos){
			Cuerpo *actual = (Cuerpo*)cuerpos->GetUserData();
			SDL_Rect dest = coordConverter.box2DToSDL(*actual);
			int id = actual->getId();
			if (id == 2) {
				camera.render(*texturas[id], dest, (((Disparo*)actual)->getAngle()) * 180/PI * -1);
			}
			if (id == ID_PORTAL_AZUL){
				camera.render(*texturas[id], dest, (((Portal*)actual)->getAnguloSalida()) * 180/PI*-1);
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
					break;
				}
				case SDL_QUIT:
					running = false;
					break;
			}
		
		}
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

