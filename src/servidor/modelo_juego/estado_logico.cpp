#include <ids.h>
#include "estado_logico.h"
#include "compuerta.h"

EstadoLogico::EstadoLogico(std::unique_ptr<Cuerpo> cuerpo):
                            cuerpo(std::move(cuerpo)){
}

bool EstadoLogico::encendida(){
	return cuerpo->estaActivado();
}

void EstadoLogico::agregar(std::shared_ptr<CompuertaLogica> compuerta_logica) {
    if (cuerpo->getId() == ID_COMPUERTA_CERRADA){
        Compuerta* compuerta = (Compuerta*)cuerpo.get();
        compuerta->agregarCompuertaLogica(compuerta_logica);
    }

}
