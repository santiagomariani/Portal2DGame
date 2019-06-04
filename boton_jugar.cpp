#include "boton_jugar.h"

#include <iostream>

BotonJugar::BotonJugar(Imagen* imagen) : Presionable(imagen){
}

void BotonJugar::presionar(){
	std::cout << "Jugar\n";
}