#include "estado_abierta.h"
#include "estado_cerrando.h"

EstadoAbierta::EstadoAbierta(){
}

EstadoCompuerta* EstadoAbierta::actualizar(bool activa){
	if (!activa){
		return new EstadoCerrando();
	}
	return new EstadoAbierta();
}

void EstadoAbierta::empezarContacto(Cuerpo* cuerpo){
}
