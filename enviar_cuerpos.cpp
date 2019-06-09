#include "enviar_cuerpos.h"
#include <cstdint>

EnviarCuerpos::EnviarCuerpos(ColaProtegida& cola, Protocolo& protocolo):
                            cola(cola), protocolo(protocolo){
    this->terminar = false;
}

void EnviarCuerpos::run(){
    while(!this->terminar){
        uint8_t msj = ENVIAR_CUERPO;
        this->protocolo.enviarMensaje(msj);

        Cuerpo* cuerpo = this->cola.topYPop();
        this->protocolo.enviarCuerpo(cuerpo);
    }
}

void EnviarCuerpos::terminar(){
    this->terminar = true;
}

EnviarCuerpos::~EnviarCuerpos(){}

