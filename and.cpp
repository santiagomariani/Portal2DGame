#include "and.h"

And::And(std::vector<CompuertaLogica>& compuertas):
			compuertas(compuertas){			
}

bool And::encendida(){
	for (auto it=compuertas.begin(); it!=compuertas.end(); it++){
		if (!(it->encendida())){
			return false;
		}
	}
	return true;
}
