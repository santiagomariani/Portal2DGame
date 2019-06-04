#include "mapa_editor.h"
#include <SDL2/SDL.h>

#include <iostream>

bool detectar_colision(SDL_Rect& A, SDL_Rect& B){
	if ((A.x >= (B.x + B.w)) || ((A.x + A.w - 1) < B.x)){
		return false;
	}
	if ((A.y >= (B.y + B.h)) || ((A.y + A.h - 1) < B.y)){
		return false;
	}
	return true;
}
int MapaEditor::convertirPosicion(int a){
	return a >= 0 ? (a / celda) * celda : ((a - celda + 1) / celda) * celda;
}
MapaEditor::MapaEditor(std::map<int, Imagen*>& img,
					   int ancho_cam, int alto_cam, int celda) :
					   imagenes(img), celda(celda){
	camara = {0, 0, ancho_cam, alto_cam};
}

void MapaEditor::agregar(int id, int x, int y, int ancho, int alto){
	x += camara.x;
	y += camara.y;
	int j = convertirPosicion(x);
	int k = convertirPosicion(y);
	mapa[j][k].id = id;
	mapa[j][k].destino = {j, k, ancho, alto};
}

void MapaEditor::quitar(int x, int y){
	x += camara.x;
	y += camara.y;
	int j = convertirPosicion(x);
	int k = convertirPosicion(y);
	//Observacion: La posicion x no se borra, a pesar de que su mapa quede vacio
	auto it = mapa.find(j);
	if (it == mapa.end()){
		return;
	}
	auto it_interno = mapa[j].find(k);
	if (it_interno == mapa[j].end()){
		return;
	}
	mapa[j].erase(it_interno);
}

void MapaEditor::render(){
	//Recorro el mapa de mapas...
	for (auto it = mapa.begin(); it != mapa.end(); ++it){
		for (auto it_interno = (it->second).begin(); it_interno != (it->second).end(); ++it_interno){
			SDL_Rect copia = (it_interno->second).destino;
			if (detectar_colision(camara, copia)){
				int id = (it_interno->second).id;
				copia.x -= camara.x;
				copia.y -= camara.y;
				imagenes[id]->render(copia);
			}
		}
	}
}

void MapaEditor::recibirEvento(SDL_KeyboardEvent& evento){
	switch (evento.keysym.sym){
		case(SDLK_UP):
			camara.y -= 10;
			break;
		case(SDLK_DOWN):
			camara.y += 10;
			break;
		case(SDLK_RIGHT):
			camara.x += 10;
			break;
		case(SDLK_LEFT):
			camara.x -= 10;
			break;
	}
}
