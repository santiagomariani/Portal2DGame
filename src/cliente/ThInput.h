//
// Created by santi on 09/06/19.
//

#ifndef THINPUT_H
#define THINPUT_H


#include "Thread.h"
#include "ColaBloqueante.h"
#include "Input.h"
#include "Protocolo.h"

class ThInput : public Thread {
private:
    ColaBloqueante<Input> &cola_input;
    Protocolo &protocolo;
public:
    ThInput(ColaBloqueante<Input> &cola_input, Protocolo &protocolo);
    void terminar();
    virtual void run();
};


#endif //THINPUT_H
