#include "and.h"

And::And(){			
}


void And::agregar(CompuertaLogica* compuerta){
	compuertas.push_back(compuerta);
}

bool And::encendida(){
	for (auto it=compuertas.begin(); it!=compuertas.end(); it++){
		if (!((*it)->encendida())){
			return false;
		}
	}
	return true;
}
