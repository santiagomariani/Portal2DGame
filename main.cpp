#include <iostream>
#include "Box2D/Box2D.h"

#include "disparo.h"
#include "roca.h"
#include "chell.h"
#include "mundo.h"
#include "estado_teclado.h"
#include "personajes.h"
#include "cuerpo.h"
#include "SdlWindow.h"
#include "ViewChell.h"
#include "contact_listener.h"

#include <thread>
#include <pthread.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

#define CONVERSION 100
#define PI 3.14159265


// En realidad es mejor que cada disparo al ser desactivado sea agregado
// a un vector de disparos_a_remover u cuerpos_a_remover y recorrer solo ese vector
void remover_disparos(Mundo& world){
	b2Body* cuerpos = world.obtenerBodies();
	while (cuerpos){
		Cuerpo* actual = (Cuerpo*)cuerpos->GetUserData();		
		int id = actual->getId();
		if (id == 2){
			((Disparo*)actual)->remover();
		}
		cuerpos = cuerpos->GetNext();
	}
}


int main() {
	b2Vec2 gravity(0.0f, -9.8f);
	Mundo world(gravity);
	ContactListenerDisparo listener_disparo;
	world.setContactListener(listener_disparo);

	Personajes personajes(world);

	std::vector<Roca> rocas;
	b2Vec2 pos(-20, -3);
	b2Vec2 inc(1, 0);
	for (int j = 0; j < 40; ++j){
		Roca roca(world, pos);
		rocas.push_back(std::move(roca));
		pos += inc;
	}

	std::vector<Roca> pared;
	b2Vec2 pos_roca(2, -3);
	b2Vec2 inc_pared(0, 1);
	for (int j = 0; j < 40; ++j){
		Roca roca(world, pos_roca);
		pared.push_back(std::move(roca));
		pos_roca += inc_pared;
	}
	//Cliente 0
	int id = personajes.agregar_chell();

//======================================SDL======================================

    const int screenWidth = 1200;
    const int screenHeight = 720;

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

    ViewChell viewChell(window);

    std::map<int,Sprite*> texturas;
    texturas[1] = &bloqueSprite;
    texturas[2] = &disparoSprite;

//======================================Loop======================================

	bool running = true;
	EstadoTeclado teclado;
	while (running) {
		SDL_Event event;
        window.fill(0x33, 0x33, 0x33, 0xFF);
		Chell& chell = personajes.obtener_chell(id);
		b2Body* cuerpos = world.obtenerBodies();
		while (cuerpos){
			Cuerpo* actual = (Cuerpo*)cuerpos->GetUserData();
			b2Vec2 position = actual->getPosition();
			int id = actual->getId();
			int posX = (position.x * CONVERSION) + (screenWidth / 2);
			int posY = (position.y * CONVERSION * -1) + (screenHeight / 2); 
			if (id == 0) {
                viewChell.render(posX, posY, 0.0f, 0.0f);
			} else if (id == 1) {
				SDL_Rect areaDest = {posX - (((Roca*)actual)->getWidth() * CONVERSION) / 2,
					posY - (((Roca*)actual)->getHeight() * CONVERSION) / 2,
					((Roca*)actual)->getWidth() * CONVERSION, 
					((Roca*)actual)->getHeight() * CONVERSION
				};
				texturas[id]->renderFrame(areaDest);
			} else if (id == 2) {
				SDL_Rect areaDest = {
					posX - (((Disparo*)actual)->getDiameter() * CONVERSION) / 2,
					posY - (((Disparo*)actual)->getDiameter() * CONVERSION) / 2,
					((Disparo*)actual)->getDiameter() * CONVERSION,
					((Disparo*)actual)->getDiameter() * CONVERSION
				}; 
				texturas[id]->renderFrame(areaDest, (((Disparo*)actual)->getAngle())*180/PI*-1);
				
			}

			cuerpos = cuerpos->GetNext();
		}

		remover_disparos(world);

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
						float x = (mouseEvent.x - screenWidth / 2) / CONVERSION;
						float y = ((mouseEvent.y - screenHeight / 2) / CONVERSION) * -1;
						b2Vec2 click(x, y);
						chell.disparar(world, click);
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
	}
	return 0;
}

