#include <path.h>
#include "texto.h"

Texto::Texto(Ventana& ventana, int tamanio) : renderizador(ventana.obtenerRenderizador()){
	textura = nullptr;
	fuente = nullptr;
	ancho = 0;
	alto = 0;
	std::string path = std::string(ASSETS) + "assets/portal.ttf";
	fuente = TTF_OpenFont(path.c_str(), tamanio);
}

bool Texto::cargarTexto(std::string textura_texto, SDL_Color color){
	SDL_Surface* superficie = TTF_RenderText_Solid(fuente, textura_texto.c_str(), color);
	if (superficie == NULL){
		printf("Error al crear superficie de texto: %s\n", TTF_GetError());
	} else {
		textura = SDL_CreateTextureFromSurface(renderizador, superficie);
		if (textura == NULL){
			printf("Error al crear textura de texto: %s\n", SDL_GetError());
		} else {
			ancho = superficie->w;
			alto = superficie->h;
		}
		SDL_FreeSurface(superficie);
	}
	return textura != NULL;
}

void Texto::render(int x, int y){
    SDL_Rect destino = {x, y, ancho, alto};
    SDL_RenderCopy(renderizador, textura, NULL, &destino);
}
