#include "enviar_cuerpos.h"
#include <cstdint>

EnviarCuerpos::EnviarCuerpos(ColaBloqueante<Cuerpo*>& cola, Protocolo& protocolo):
                            cola(cola), protocolo(protocolo){
    this->terminar = false;
}

void EnviarCuerpos::run(){
    while(!this->terminar){
        Cuerpo* cuerpo;
        if (!(this->cola.pop(*cuerpo))){
            continue;
        }
        uint8_t msj = ENVIAR_CUERPO;
        this->protocolo.enviarMensaje(msj);
        this->protocolo.enviarCuerpo(cuerpo);
    }
}

void EnviarCuerpos::terminar(){
    this->terminar = true;
}

EnviarCuerpos::~EnviarCuerpos(){}

