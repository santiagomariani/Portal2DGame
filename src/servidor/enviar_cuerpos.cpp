#include "enviar_cuerpos.h"
#include "cuerpo_a_enviar.h"
#include <cstdint>
#include <iostream>

#define ENVIAR_CUERPO 4

EnviarCuerpos::EnviarCuerpos(ColaBloqueanteCuerpos* cola, Protocolo& protocolo):
                            cola(cola), protocolo(protocolo){
    this->terminar_envio = false;
}

void EnviarCuerpos::run(){
    while(!this->terminar_envio){
        CuerpoAEnviar cuerpo_a_enviar;
        if (!(this->cola->pop(cuerpo_a_enviar))){ // se puede usar struct o usar colas con punteros
            continue;
        }
        std::cout << "popeo cuerpo\n";
        if (cuerpo_a_enviar.ultimo){
            this->protocolo.enviarFinalizoFotograma();
        } else{
            std::cout << "cuerpo enviado\n";
            this->protocolo.enviarCuerpo(*cuerpo_a_enviar.cuerpo);
        }
    }
}

void EnviarCuerpos::terminar(){
    this->terminar_envio = true;
}

EnviarCuerpos::~EnviarCuerpos(){}

