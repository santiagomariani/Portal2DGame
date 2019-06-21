#include "boton_mapa.h"

#define SEPARADOR 20
#define TAMANIO 30

BotonMapa::BotonMapa(Imagen* imagen, std::string& mapa_elegido, 
					 std::string& nombre_mapa, Ventana& ventana) : 
					 Presionable(imagen), mapa_elegido(mapa_elegido),
					 nombre_mapa(nombre_mapa), mensaje(ventana, TAMANIO){
	mensaje.cargarTexto(nombre_mapa.c_str(), color);
}

void BotonMapa::render(){
	mensaje.render(destino.x + SEPARADOR, destino.y + SEPARADOR);
	Presionable::render();
}

void BotonMapa::presionar(){
	mapa_elegido = nombre_mapa;
}

void BotonMapa::mover(int offset_x, int offset_y){
	destino.x += offset_x;
	destino.y += offset_y;
}
