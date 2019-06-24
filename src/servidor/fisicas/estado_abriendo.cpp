#include "estado_abriendo.h"
#include "estado_abierta.h"
#include <iostream>

EstadoAbriendo::EstadoAbriendo(){
}

EstadoCompuerta* EstadoAbriendo::actualizar(bool activa, b2Body* puerta){
	return new EstadoAbierta();
}

void EstadoAbriendo::empezarContacto(Cuerpo* cuerpo){
}

int EstadoAbriendo::getId(){
	return ID_COMPUERTA_ABRIENDO;
}
