#include "estado_abierta.h"
#include "estado_cerrando.h"

EstadoAbierta::EstadoAbierta(){
}

EstadoCompuerta* EstadoAbierta::actualizar(bool activa, b2Body* puerta){
	if (!activa){
		puerta->SetActive(true); // activar por si estaba desactivado
		return new EstadoCerrando();
	}
	puerta->SetActive(false); // desactivar cuerpo, no colisiona
	return new EstadoAbierta();
}

void EstadoAbierta::empezarContacto(Cuerpo* cuerpo){
}

int EstadoAbierta::getId(){
	return ID_COMPUERTA_ABIERTA;
}
