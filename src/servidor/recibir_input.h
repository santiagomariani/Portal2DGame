#ifndef RECIBIR_INPUT_H
#define RECIBIR_INPUT_H

#include "ColaBloqueante.h"
#include "Protocolo.h"
#include "Thread.h"
#include "Input.h"

class RecibirInput : public Thread {
private:
    ColaBloqueante<Input>& cola;
    Protocolo& protocolo;
    bool terminar_proceso;

public:
    explicit RecibirInput(ColaBloqueante<Input>& cola, Protocolo& protocolo);

    void run() override;

    void terminar();

    ~RecibirInput();
};

#endif

