#include "pieza.h"

Pieza::Pieza(){
}

Pieza::Pieza(int id,
		int ancho,
		int alto,
		Imagen* imagen,
		bool logica,
		int identificador) :
			 ancho(ancho),
			 alto(alto),
			 identificador(identificador),
			 logica(logica),
			 imagen(imagen),
			 id(id) {
}

int Pieza::getAncho(){
	return ancho;
}

int Pieza::getAlto(){
	return alto;
}

void Pieza::render(SDL_Rect destino){
	imagen->render(destino);
}

int Pieza::getIdentificador(){
	return identificador;
}