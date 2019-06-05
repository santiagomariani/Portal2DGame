#include "imagen.h"

Imagen::Imagen() : textura(nullptr){
	alto = 0;
	ancho = 0;
}
Imagen::Imagen(int area_x, int area_y, int ancho, int alto,
	   		   SdlTexture* textura) :
			   alto(alto), ancho(ancho), textura(textura){
	area.x = area_x;
	area.y = area_y;
	area.w = ancho;
	area.h = alto;
}
Imagen::Imagen(Imagen&& otra) : textura(otra.textura){
	if (&otra == this){
		return;
	}
	alto = otra.alto;
	ancho = otra.ancho;
	area = std::move(otra.area);
}
void Imagen::render(SDL_Rect& destino){
	textura->render(&area, &destino);
}