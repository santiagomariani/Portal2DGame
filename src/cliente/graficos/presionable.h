#ifndef PRESIONABLE_H
#define PRESIONABLE_H

#include <SDL2/SDL.h>
#include "imagen.h"


// Clase padre para todos los botones 
class Presionable{
	Imagen* imagen;
protected:
	SDL_Rect destino; //El boton tiene un destino fijo y es unico
public:
	Presionable(Imagen* imagen);

	// Setea el tamanio y la posicion del boton
	void colocar(int x, int y, int ancho, int alto);

	// Recibe el evento del mouse y checkea si se esta haciendo click sobre el;
	// si se esta haciendo click sobre el se ejecuta presionar()
	void recibirEvento(SDL_MouseButtonEvent& click);

	// Se agrega a la ventana para el siguiente render
	void render();

	// La accion que ejecuta el boton
	virtual void presionar() = 0;
};

#endif //PRESIONABLE