#include "boton_editar.h"

BotonEditar::BotonEditar(Imagen* imagen, int* etapa, bool* corriendo) :
						 Presionable(imagen), etapa(etapa), corriendo(corriendo){
}

void BotonEditar::presionar(){
	*etapa = 1;
	*corriendo = false;
}
