#include "boton_jugar.h"

#include <iostream>

BotonJugar::BotonJugar(Imagen* imagen, int* etapa, bool* corriendo) :
					   Presionable(imagen), etapa(etapa), corriendo(corriendo){
}

void BotonJugar::presionar(){
	std::cout << "Jugar\n";
	*etapa = 2;
    *corriendo = false;
}