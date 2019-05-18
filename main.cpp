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
	b2World world(gravity);

	std::vector<Roca> roquitas;
	b2Vec2 pos(-50, 0);
	b2Vec2 inc(1, 0);
	for (int j = 0; j < 1000; ++j){
		Roca roca(world, pos);
		pos += inc;
		roquitas.push_back(roca);
	}
	/*b2Body* piso_cuerpo;
	b2BodyDef piso_def;
	piso_def.type = b2_staticBody;
	piso_def.position.Set(0, 0);
	piso_def.angle = 0;
	piso_cuerpo = world.CreateBody(&piso_def);

	b2Vec2 piso1(-1000, 0);
	b2Vec2 piso2(1000, 0);
	b2EdgeShape piso;
	piso.Set(piso1, piso2);
	b2FixtureDef figura;
	figura.shape = &piso;
	piso_cuerpo->CreateFixture(&figura);*/


	b2Vec2 pos_chell(0, 3);
	Chell chell(world, pos_chell);

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;



	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(1600, 800, SDL_RENDERER_ACCELERATED, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
	SDL_RenderClear(renderer);
	SDL_Texture* texture = IMG_LoadTexture(renderer, "roquita.jpeg");
	bool running = true;

	EstadoTeclado teclado;
	while (running) {
		SDL_Event event;
		//SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
		SDL_Rect sdlSrc = {
		0, 0,
		233, 216
		};
		b2Vec2 chell_pos = chell.getPosition();
		SDL_Rect sdlDest = {
		(int)(chell_pos.x * CONVERSION) + 400, (int)(chell_pos.y * CONVERSION * -1) + 300,
		233, 216
		};
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