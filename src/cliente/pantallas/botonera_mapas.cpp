#include "botonera_mapas.h"
#include "ids.h"
#include <iostream>

#define SEPARACION 20
#define CANT_BOTONES 5

BotoneraMapas::BotoneraMapas(Imagen* fondo, SDL_Rect& destino) :
				    fondo(fondo), destino_panel(destino){
}

void BotoneraMapas::setBotones(std::vector<BotonMapa>* _botones){
	botones = _botones;
	SDL_Rect pos_boton = {destino_panel.x + SEPARACION, destino_panel.y + SEPARACION,
						  destino_panel.w - (2 * SEPARACION), destino_panel.h / CANT_BOTONES};
	for (auto it = botones->begin(); it != botones->end(); ++it){
		(*it).colocar(pos_boton.x, pos_boton.y, pos_boton.w, pos_boton.h);
		pos_boton.y += (pos_boton.h + SEPARACION);
	}
}

void BotoneraMapas::render(){
	fondo->render(destino_panel);

	for (auto it = botones->begin(); it != botones->end(); ++it){
		(*it).render();
	}
}

bool BotoneraMapas::colisiona(int x, int y){
	return (x >= destino_panel.x && x <= (destino_panel.x + destino_panel.w) &&
		y >= destino_panel.y && y <= (destino_panel.y + destino_panel.h));
}

void BotoneraMapas::recibirEvento(SDL_MouseButtonEvent& evento){
	for (auto it = botones->begin(); it != botones->end(); ++it){
		(*it).recibirEvento(evento);
	}
}

void BotoneraMapas::recibirEvento(SDL_MouseWheelEvent& evento){
	for (auto it = botones->begin(); it != botones->end(); ++it){
		(*it).mover(0, evento.y * 15);
	}
}
