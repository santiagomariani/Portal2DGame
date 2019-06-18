#include "or.h"

Or::Or(){
}

void Or::agregar(std::shared_ptr<CompuertaLogica> compuerta){
	compuertas.push_back(compuerta);
}

bool Or::encendida(){
	for (auto it=compuertas.begin(); it!=compuertas.end(); it++){
		if (((*it)->encendida())){
			return true;
		}
	}
	return false;
}
