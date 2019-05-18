#include <iostream>
//#include "ejemplo.h"
#include "Box2D/Box2D.h"
#include "disparo.h"
#include "roca.h"
#include "chell.h"
#include "estado_teclado.h"
#include <thread>
#include <pthread.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#define CONVERSION 10

int main() {
	b2Vec2 gravity(0.0f, -9.8f);
	Mundo world(gravity);

	b2Vec2 pos(-50, 0);
	b2Vec2 inc(1, 0);
	for (int j = 0; j < 1000; ++j){
		world.crearRoca(pos);
		pos += inc;
	}

	b2Vec2 pos_chell(0, 3);
	world.crearChell(0, pos_chell); //Cliente 0


//======================================SDL======================================



	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(1600, 800, SDL_RENDERER_ACCELERATED, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
	SDL_RenderClear(renderer);
	SDL_Texture* textura_chell = IMG_LoadTexture(renderer, "chell.jpeg");
	SDL_Texture* textura_roca = IMG_LoadTexture(renderer, "roca.jpg");
	SDL_Texture* textura_disparo = IMG_LoadTexture(renderer, "disparo.jpg");
	

//======================================Loop======================================

	bool running = true;
	EstadoTeclado teclado;
	while (running) {
		SDL_Event event;
		


		const b2world w = world.getMundo();

		b2Body* lista = w.GetBodyList();

		int i = 0;
		while (lista[i]){
			void* objeto = lista[i].getUserData();
		}

		/*SDL_Rect sdlSrc = {
		0, 0,
		233, 216
		};
		b2Vec2 chell_pos = chell.getPosition();
		SDL_Rect sdlDest = {
		(int)(chell_pos.x * CONVERSION) + 400, (int)(chell_pos.y * CONVERSION * -1) + 300,
		233, 216
		};*/
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, &sdlSrc, &sdlDest);


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

					}

				}
				case SDL_QUIT:
					running = false;
					break;
			}
		
		}
		chell.mover_con_evento(teclado);
		world.Step(timeStep, velocityIterations, positionIterations);
		SDL_RenderPresent(renderer);
	}
	return 0;
}