#include "constructor_piezas.h"
#include "ids.h"

ConstructorDePiezas::ConstructorDePiezas(std::map<int, Imagen*>& imagenes) : 
										 imagenes(imagenes){
}

Pieza ConstructorDePiezas::construir(int id){
	if (id == ID_BOTON_APAGADO || id == ID_AND || id == ID_OR){
		identificador++;
		return Pieza(id, 1, 1, imagenes[id], true, identificador);
	}
	if (id == ID_COMPUERTA_CERRADA){
		identificador++;
		return Pieza(id, 1, 2, imagenes[id], true, identificador);
	}
	return Pieza(id, 1, 1, imagenes[id], false, -1);
}