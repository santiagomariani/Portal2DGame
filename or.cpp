#include "or.h"

Or::Or(std::vector<CompuertaLogica>& compuertas):
			compuertas(compuertas){			
}

bool Or::encendida(){
	for (auto it=compuertas.begin(); it!=compuertas.end(); it++){
		if (!(it->encendida())){
			return false;
		}
	}
	return true;
}
