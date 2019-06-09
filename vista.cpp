#include "vista.h"
#include "estado_mouse.h"
#include "CoordConverter.h"
#include "ViewChell.h"
#include "InfoCuerpo.h"
#include "ids.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "Box2D/Box2D.h"

#define FPS 60
#define TICKS_PER_FRAME 1000/FPS

Vista::Vista(SdlWindow& ventana, Camera& camara, Protocolo& protocolo,
			 std::map<int, Renderable*> texturas): 
			protocolo(protocolo), ventana(ventana), 
			camara(camara), texturas(texturas){
}

bool Vista::obtenerInput(CoordConverter& coordConverter){
	EstadoMouse mouse;
	SDL_Event event;
	bool seguir = true;
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
					b2Vec2 click = coordConverter.sdlToBox2D(mouseEvent.x, mouseEvent.y, camara);
					mouse.agregarClickIzquierdo(click);
				}
				if ((mouseEvent.button) == SDL_BUTTON_RIGHT){
					b2Vec2 click = coordConverter.sdlToBox2D(mouseEvent.x, mouseEvent.y, camara);
					mouse.agregarClickDerecho(click);
				}
				break;
			}
			case SDL_QUIT:
				seguir = false;
		}	
	}
	protocolo.enviarTeclado(teclado);
	return seguir;
}


void Vista::renderizar(){
	fpsTimer.start();
	ventana.fill(0x33, 0x33, 0x33, 0xFF); 
	camara.renderBg(); 
	int cant  = protocolo.recibirCant();
	while (!(protocolo.termino())){
		struct InfoCuerpo cuerpo_info;
		protocolo.recibirCuerpo(cuerpo_info);

		SDL_Rect dest = cuerpo_info.dest;
		int id = cuerpo_info.id;
		int estado = cuerpo_info.estado;
		double angulo = cuerpo_info.angulo;

		if (id == ID_DISPARO) {
			camara.render(*texturas[id], dest, angulo);
		} else if (id == ID_PORTAL_AZUL || id == ID_PORTAL_NARANJA){
			camara.render(*texturas[id], dest, angulo);
		} else if (id == ID_BOLAENERGIA) {
			camara.render(*texturas[id], dest, angulo);
		} else if (id == ID_CHELL) {
			camara.updateCamera(dest); // tiene que ser la chell del cliente
			((ViewChell*)texturas[id])->cambiarEstado(estado);
			SDL_RendererFlip flip = cuerpo_info.flip;
			camara.render(*texturas[id], dest, 0, nullptr, flip);
		} else {
			camara.render(*texturas[id], dest);
		}
	}
	ventana.render();

	int frameTicks = capTimer.getTicks();
	if (frameTicks < TICKS_PER_FRAME) {
		SDL_Delay(TICKS_PER_FRAME - frameTicks);
	}
}

