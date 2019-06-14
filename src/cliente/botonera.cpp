#include "botonera.h"
#include "ids.h"
#include <iostream>

Botonera::Botonera(Imagen* fondo, int ancho_v, int alto_v) :
				    fondo(fondo){

	int alto_panel = alto_v;
	int ancho_panel = ancho_v / 6;
	int pos_panel_y = 0;
	int pos_panel_x =  ancho_v - ancho_panel;
	destino_panel = {pos_panel_x, pos_panel_y, ancho_panel, alto_panel};

	separacion = ancho_panel / 4;
	lado_boton = ancho_panel / 2;
}

void Botonera::setBotones(std::vector<BotonBloque>* _botones){
	botones = _botones;
	SDL_Rect pos_boton = {separacion + destino_panel.x, separacion,
						  lado_boton, lado_boton};
	for (auto it = botones->begin(); it != botones->end(); ++it){
		(*it).colocar(pos_boton.x, pos_boton.y, pos_boton.w, pos_boton.h);
		pos_boton.y += (separacion + lado_boton);
	}
}

void Botonera::render(){
	fondo->render(destino_panel);

	for (auto it = botones->begin(); it != botones->end(); ++it){
		(*it).render();
	}
}

bool Botonera::colisiona(int x, int y){
	return (x >= destino_panel.x);
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
