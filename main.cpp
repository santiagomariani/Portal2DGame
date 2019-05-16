#include <iostream>
//#include "ejemplo.h"
#include "Box2D/Box2D.h"
#include "disparo.h"
#include "roca.h"
#include "chell.h"
#include <thread>
#include <pthread.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#define CONVERSION 25


class Accion{
	Chell& chell;
public:
	Accion(Chell& c) : chell(c){
	}
	void operator()(){
		char c;
		bool caca = true;
		while (caca){
			c = std::cin.get();
			if (c == 'w'){
				chell.saltar();
			}else if (c == 'a'){
				chell.moverIzquierda();
			}else if (c == 's'){
				caca = false;
			}else if (c == 'd'){
				chell.moverDerecha();
			}
		}
	}
};

int main() {
	b2Vec2 gravity(0.0f, -9.8f);
	b2World world(gravity);

	/*std::vector<Roca> roquitas;
	b2Vec2 pos(-50, 0);
	b2Vec2 inc(1, 0);
	for (int j = 0; j < 100; ++j){
		Roca roca(world, pos);
		pos += inc;
		roquitas.push_back(roca);
	}*/
	b2Body* piso_cuerpo;
	b2BodyDef piso_def;
	piso_def.type = b2_staticBody;
	piso_def.position.Set(0, 0);
	piso_def.angle = 0;
	piso_cuerpo = world.CreateBody(&piso_def);

	b2Vec2 piso1(-100, 0);
	b2Vec2 piso2(100, 0);
	b2EdgeShape piso;
	piso.Set(piso1, piso2);
	b2FixtureDef figura;
	figura.shape = &piso;
	piso_cuerpo->CreateFixture(&figura);


	b2Vec2 pos_chell(0, 3);
	Chell chell(world, pos_chell);

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;



	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(1600, 1200, SDL_RENDERER_ACCELERATED, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
	SDL_RenderClear(renderer);
	SDL_Texture* texture = IMG_LoadTexture(renderer, "roquita.jpeg");
	bool running = true;

	//b2Vec2 movimiento(0, 0);

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
		//while (SDL_PollEvent(&event) != 0){
		SDL_PumpEvents();
			const Uint8 *state = SDL_GetKeyboardState(NULL);
				/*if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {
			    	chell.moverIzquierda();
			    	chell.saltar();
			    	continue;
				}
				if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
			    	chell.moverDerecha();
			    	chell.saltar();
			    	continue;
				}*/
			chell.mover(state);
			if (state[SDL_SCANCODE_0]){
				running = false;
			}
			/*switch(event.type) {
				case SDL_KEYDOWN: {
						SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
						switch (keyEvent.keysym.sym) {
							case SDLK_LEFT:
								chell.moverIzquierda();
								break;
							case SDLK_RIGHT:
								chell.moverDerecha();
								break;
							case SDLK_UP:
								chell.saltar();
								break;
							case SDLK_DOWN:
								return 0;
								break;
							}
					}
					break;
				case SDL_QUIT:
	                std::cout << "Quit :(" << std::endl;
	                running = false;
	                break;
			}*/
		//}
		//std::cout << "Chell:" << chell_pos.x << " " << chell_pos.y << '\n';
		world.Step(timeStep, velocityIterations, positionIterations);
		SDL_RenderPresent(renderer);
	}
	return 0;
}