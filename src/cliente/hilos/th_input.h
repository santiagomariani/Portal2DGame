
#ifndef TH_INPUT_H
#define TH_INPUT_H


#include "thread.h"
#include "cola_bloqueante.h"
#include "input.h"
#include "protocolo.h"

class ThInput : public Thread {
private:
    ColaBloqueante<Input> &cola_input;
    Protocolo &protocolo;
    uint8_t id;
    
public:
    ThInput(ColaBloqueante<Input> &cola_input, Protocolo &protocolo, uint8_t id);
    // Saca de la cola de input el input obtenido en el cliente para enviarlo
    // luego al servidor.
    virtual void run();
    // Deja de enviar input.
    void terminar();
};


#endif //TH_INPUT_H
