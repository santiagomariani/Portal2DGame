#include "estado_logico.h"

EstadoLogico::EstadoLogico(Cuerpo& cuerpo): cuerpo(cuerpo){
}

bool EstadoLogico::encendida(){
	return cuerpo.encendido();
}
