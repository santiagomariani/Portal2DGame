#include "boton_mapa.h"

#define SEPARADOR 7
#define TAMANIO 30

BotonMapa::BotonMapa(Imagen* imagen, std::string& mapa_elegido, 
					 std::string& nombre_mapa, Ventana& ventana) : 
					 Presionable(imagen), mapa_elegido(mapa_elegido),
					 nombre_mapa(nombre_mapa), mensaje(ventana, TAMANIO){
	mensaje.cargarTexto(nombre_mapa.c_str(), color);
}

void BotonMapa::render(){
	Presionable::render();
	mensaje.render(destino.x + SEPARADOR, destino.y + SEPARADOR);
}

void BotonMapa::presionar(){
	mapa_elegido = nombre_mapa;
}

void BotonMapa::mover(int offset_x, int offset_y){
	destino.x += offset_x;
	destino.y += offset_y;
}

bool BotonMapa::estaDentro(SDL_Rect& espacio){
	bool punto_sup_izq = (destino.x >= espacio.x &&
						  destino.x <= (espacio.x + espacio.w) &&
						  destino.y >= espacio.y &&
						  destino.y <= (espacio.y + espacio.h));

	bool punto_inf_der = (destino.x + destino.w >= espacio.x &&
						  destino.x + destino.w <= (espacio.x + espacio.w) &&
						  destino.y + destino.h >= espacio.y &&
						  destino.y + destino.h <= (espacio.y + espacio.h));
	return punto_sup_izq && punto_inf_der;
}

