#include "presionable.h"

Presionable::Presionable(Imagen* imagen) : imagen(imagen){
}

void Presionable::colocar(int x, int y, int ancho, int alto){
	destino.x = x;
	destino.y = y;
	destino.w = ancho;
	destino.h = alto;
}

void Presionable::render(){
	imagen->render(destino);
}

void Presionable::recibirEvento(SDL_MouseButtonEvent& click){
	if (!(click.button == SDL_BUTTON_LEFT)){
		return;
	}
	//Si el click fue dentro del boton...
	if (click.x >= destino.x && click.x <= (destino.x + destino.w) &&
		click.y >= destino.y && click.y <= (destino.y + destino.h)){
		presionar();
	}
}
