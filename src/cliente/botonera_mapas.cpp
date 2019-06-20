#include "botonera_mapas.h"
#include "ids.h"
#include <iostream>

Botonera::Botonera(Imagen* fondo, SDL_Rect& destino_panel) :
				    fondo(fondo), destino_panel(destino_panel){
}

void Botonera::setBotones(std::vector<BotonBloque>* _botones){
	botones = _botones;
	SDL_Rect pos_boton = {destino_panel.x + 20, destino_panel.y + 20,
						  destino_panel.w - 40, 60};
	for (auto it = botones->begin(); it != botones->end(); ++it){
		(*it).colocar(pos_boton.x, pos_boton.y, pos_boton.w, pos_boton.h);
		pos_boton.y += 80;
	}
}

void Botonera::render(){
	fondo->render(destino_panel);

	for (auto it = botones->begin(); it != botones->end(); ++it){
		(*it).render();
	}
}

bool Botonera::colisiona(int x, int y){
	return (x >= destino_panel.x && x <= (destino_panel.x + destino_panel.w) &&
        y >= destino_panel.y && y <= (destino_panel.y + destino_panel.h));
}

void Botonera::recibirEvento(SDL_MouseButtonEvent& evento){
	for (auto it = botones->begin(); it != botones->end(); ++it){
		(*it).recibirEvento(evento);
	}
}

void Botonera::recibirEvento(SDL_MouseWheelEvent& evento){
	for (auto it = botones->begin(); it != botones->end(); ++it){
		(*it).mover(0, evento.y * 15);
	}
}
