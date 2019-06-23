#include "boton_escribir.h"

BotonEscribir::BotonEscribir(Imagen* imagen, bool* escribir) :
							 Presionable(imagen), escribir(escribir){
}

void BotonEscribir::presionar(){
	*escribir = !(*escribir);
}
