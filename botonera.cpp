#include "botonera.h"
#include "ids.h"


Botonera::Botonera(std::map<int, Imagen*>& imagenes, Cursor& cursor,
				   Imagen* fondo, int ancho_v, int alto_v, int celda) :
				   fondo(fondo), ancho_v(ancho_v), alto_v(alto_v){

	int alto_panel = alto_v;
	int ancho_panel = ancho_v / 6;
	int pos_panel_y = 0;
	int pos_panel_x =  ancho_v - ancho_panel;
	division = pos_panel_x;
	destino_panel = {pos_panel_x, pos_panel_y, ancho_panel, alto_panel};

	botones.emplace_back(cursor, ID_BLOQUE_ROCA, celda, celda, imagenes[ID_BLOQUE_ROCA]);
	botones.emplace_back(cursor, ID_BLOQUE_METAL, celda, celda, imagenes[ID_BLOQUE_METAL]);

	int separacion = ancho_panel / 4;
	int medida_boton = ancho_panel / 2;

	SDL_Rect pos_boton = {separacion + pos_panel_x, separacion,
						  medida_boton, medida_boton};
	for (auto it = botones.begin(); it != botones.end(); ++it){
		(*it).colocar(pos_boton.x, pos_boton.y, pos_boton.w, pos_boton.h);
		pos_boton.y += (separacion + medida_boton);
	}
}

void Botonera::render(){
	fondo->render(destino_panel);

	for (auto it = botones.begin(); it != botones.end(); ++it){
		(*it).render();
	}
}

bool Botonera::colisiona(int x, int y){
	return (x >= division);
}

void Botonera::recibirEvento(SDL_MouseButtonEvent& evento){
	for (auto it = botones.begin(); it != botones.end(); ++it){
		(*it).recibirEvento(evento);
	}
}

void Botonera::recibirEvento(SDL_MouseWheelEvent& evento){
	for (auto it = botones.begin(); it != botones.end(); ++it){
		(*it).mover(0, evento.y * 15);
	}
}
