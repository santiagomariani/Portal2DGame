#include "boton_volver.h"

BotonVolver::BotonVolver(Imagen* imagen, int* etapa, bool* corriendo) :
						 Presionable(imagen), etapa(etapa), corriendo(corriendo){
}

void BotonVolver::presionar(){
	*etapa = 0;
	*corriendo = false;
}
