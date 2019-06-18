#include "constructor_piezas.h"
#include "ids.h"

ConstructorDePiezas::ConstructorDePiezas(std::map<int, Imagen*>& imagenes) : 
										 imagenes(imagenes){
}

Pieza ConstructorDePiezas::construir(int id){
	switch(id){
		case(ID_BOTON_APAGADO):
		case(ID_RECEPTORARRIBA_DESACTIVADO):
		case(ID_RECEPTORABAJO_DESACTIVADO):
		case(ID_RECEPTORIZQUIERDA_DESACTIVADO):
		case(ID_RECEPTORDERECHA_DESACTIVADO):
		case(ID_AND):
		case(ID_OR):
			identificador++;
			return Pieza(id, 1, 1, imagenes[id], true, identificador);
		case(ID_COMPUERTA_CERRADA):
			identificador++;
			return Pieza(id, 1, 2, imagenes[id], true, identificador);
		case(ID_BARRAENERGIA):
			return Pieza(id, 1, 2, imagenes[id], false, -1);
	}
	return Pieza(id, 1, 1, imagenes[id], false, -1);
}