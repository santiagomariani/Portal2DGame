#ifndef TEXTO_H
#define TEXTO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "SdlWindow.h"
#include <string>

class Texto{
	SDL_Texture* textura;
	SDL_Renderer* renderizador;
	TTF_Font* fuente;
	int ancho;
	int alto;

public:
	Texto(SdlWindow& ventana, int tamanio);
	bool cargarTexto(std::string textura_texto, SDL_Color color);
	void render(int x, int y);
};

#endif //TEXTO