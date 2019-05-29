#include "estado_cerrando.h"
#include "estado_cerrada.h"
#include "ids.h"
#include "chell.h"
#include <iostream>

EstadoCerrando::EstadoCerrando(){
}

EstadoCompuerta* EstadoCerrando::actualizar(bool activa){
	std::cout << "cerrando a cerrar\n";
	return new EstadoCerrada();
}

void EstadoCerrando::empezarContacto(Cuerpo* cuerpo){
	if (cuerpo->getId() == ID_CHELL){
		((Chell*)cuerpo)->morir();
	}
}
