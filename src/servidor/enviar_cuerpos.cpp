#include "enviar_cuerpos.h"
#include "cuerpo_a_enviar.h"
#include "socket_error.h"
#include <cstdint>
#include <iostream>


EnviarCuerpos::EnviarCuerpos(ColaBloqueanteCuerpos* cola, Protocolo& protocolo):
                            cola(cola), protocolo(protocolo){
    this->terminar_envio = false;
}

void EnviarCuerpos::run(){
    while(!this->terminar_envio){
        CuerpoAEnviar cuerpo_a_enviar;
        if (!(this->cola->pop(cuerpo_a_enviar))){
            std::cout << "not pop\n";
            continue;
        }
        try{
            if (cuerpo_a_enviar.ultimo){
                this->protocolo.enviarFinalizoFotograma();
            } else {
                this->protocolo.enviarCuerpo(cuerpo_a_enviar.info_cuerpo);
            }
        } catch(const SocketError &e){
            this->terminar_envio = true;
            std::cout << "se desconecto un cliente.\n";
        }
    }
}

void EnviarCuerpos::terminar(){
    this->terminar_envio = true;
}

EnviarCuerpos::~EnviarCuerpos(){}

