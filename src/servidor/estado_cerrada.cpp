#include "estado_cerrada.h"
#include "estado_abriendo.h"
#include <iostream>

EstadoCerrada::EstadoCerrada(){
}

EstadoCompuerta* EstadoCerrada::actualizar(bool activa, b2Body* puerta){
	if (!activa){
		return new EstadoCerrada();
	}
	return new EstadoAbriendo();
}

void EstadoCerrada::empezarContacto(Cuerpo* cuerpo){
}
int EstadoCerrada::getId(){
	return ID_COMPUERTA_CERRADA;
}
