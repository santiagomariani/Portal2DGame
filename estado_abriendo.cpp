#include "estado_abriendo.h"
#include "estado_abierta.h"
#include <iostream>

EstadoAbriendo::EstadoAbriendo(){
}

EstadoCompuerta* EstadoAbriendo::actualizar(bool activa){
	std::cout << "abriendo a abierta\n";
	return new EstadoAbierta();
}

void EstadoAbriendo::empezarContacto(Cuerpo* cuerpo){
}
