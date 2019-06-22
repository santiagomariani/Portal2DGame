#include "boton_aceptar.h"

#define SEPARADOR 7
#define TAMANIO 30

BotonAceptar::BotonAceptar(Imagen* imagen, bool* continuar, 
							Ventana& ventana, 
							Protocolo& protocolo,
							std::string& mapa_elegido) : 
					 Presionable(imagen), 
					 continuar(continuar),
					 mensaje(ventana, TAMANIO),
					 protocolo(protocolo),
					 mapa_elegido(mapa_elegido){
	aceptar = "Aceptar";
	mensaje.cargarTexto(aceptar.c_str(), color);
}

void BotonAceptar::render(){
	Presionable::render();
	mensaje.render(destino.x + SEPARADOR, destino.y + SEPARADOR);
}

void BotonAceptar::presionar(){
	protocolo.enviarNombreMapa(mapa_elegido);
	*continuar = false;
}

void BotonAceptar::mover(int offset_x, int offset_y){
	destino.x += offset_x;
	destino.y += offset_y;
}
