#include "boton_guardar.h"
#include <iostream>

BotonGuardar::BotonGuardar(Imagen* imagen, MapaEditor& mapa, std::string& nombre) : 
						   Presionable(imagen), mapa(mapa), nombre(nombre){
}
void BotonGuardar::presionar(){
	mapa.guardar(nombre);
}