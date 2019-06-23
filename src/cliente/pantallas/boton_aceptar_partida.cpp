#include "boton_aceptar_partida.h"

#define SEPARADOR 7
#define TAMANIO 30

BotonAceptarPartida::BotonAceptarPartida(Imagen* imagen, bool* continuar, 
							Ventana& ventana, std::string& puerto_elegido,
							std::string& puerto) : 
					 Presionable(imagen), 
					 continuar(continuar),
					 mensaje(ventana, TAMANIO),
					 puerto_elegido(puerto_elegido),
					 puerto(puerto){
	aceptar = "Aceptar";
	mensaje.cargarTexto(aceptar.c_str(), color);
}

void BotonAceptarPartida::render(){
	Presionable::render();
	mensaje.render(destino.x + SEPARADOR, destino.y + SEPARADOR);
}

void BotonAceptarPartida::presionar(){
	puerto.assign(puerto_elegido);
	*continuar = false;
}

void BotonAceptarPartida::mover(int offset_x, int offset_y){
	destino.x += offset_x;
	destino.y += offset_y;
}
