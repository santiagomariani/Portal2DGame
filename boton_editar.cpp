#include "boton_editar.h"

#include <iostream>

BotonEditar::BotonEditar(Imagen* imagen) : Presionable(imagen){
}

void BotonEditar::presionar(){
	std::cout << "Modo Editor (Proximamente...)\n";
}
