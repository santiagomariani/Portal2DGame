#include "estado_cerrada.h"
#include "estado_abriendo.h"
#include <iostream>

EstadoCerrada::EstadoCerrada(){
}

EstadoCompuerta* EstadoCerrada::actualizar(bool activa){
	if (!activa){
		return new EstadoCerrada();
	}
	std::cout << "cerrada a abriendo\n";
	return new EstadoAbriendo();
}

void EstadoCerrada::empezarContacto(Cuerpo* cuerpo){
}
