#include "pieza.h"

Pieza::Pieza(){
}

Pieza::Pieza(int id, int ancho, int alto, Imagen* imagen, bool logica, int identificador) : 
			 id(id), ancho(ancho), alto(alto), imagen(imagen), logica(logica), identificador(identificador){
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