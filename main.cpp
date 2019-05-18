#include <iostream>
//#include "ejemplo.h"
#include "Box2D/Box2D.h"
#include "disparo.h"
#include "roca.h"
#include "chell.h"
#include "mundo.h"
#include "estado_teclado.h"
#include "personajes.h"
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

	Personajes personajes(world);

	b2Vec2 pos(-50, -3);
	b2Vec2 inc(1, 0);
	for (int j = 0; j < 1000; ++j){
		world.crearRoca(pos);
		pos += inc;
	}
	//Cliente 0
	int id = personajes.agregar_chell();

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
		SDL_RenderClear(renderer);
		std::map<int, Chell>& mapa = personajes.getPersonajes();
		b2Vec2 chell_pos = mapa[id].getPosition();
		SDL_Rect sdlSrc = {
		0, 0,
		233, 216
		};
		SDL_Rect sdlDest = {
		(int)(chell_pos.x * CONVERSION) + 400, (int)(chell_pos.y * CONVERSION * -1) + 300,
		233, 216
		};
		SDL_RenderCopy(renderer, textura_chell, &sdlSrc, &sdlDest);
		std::vector<Disparo>& disparitos = world.getDisparos();
		for (auto it = disparitos.begin(); it != disparitos.end(); ++it){
			b2Vec2 asd = (*it).getPosition();
			SDL_Rect sdlSrc_a = {
			0, 0,
			1024, 1024
			};
			SDL_Rect sdlDest_a = {
			(int)(asd.x * CONVERSION) + 400, (int)(asd.y * CONVERSION * -1) + 300,
			100, 100
			};
			SDL_RenderCopy(renderer, textura_disparo, &sdlSrc_a, &sdlDest_a);
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
						float x = (mouseEvent.x - 400) / CONVERSION;
						float y = ((mouseEvent.y - 300) / CONVERSION) * -1;
						b2Vec2 click(x, y);
						personajes.disparar(id, click);
					}
					break;
				}
				case SDL_QUIT:
					running = false;
					break;
			}
		
		}
		personajes.mover_chell(id, teclado);
		world.avanzar();
		SDL_RenderPresent(renderer);
	}
	return 0;
}