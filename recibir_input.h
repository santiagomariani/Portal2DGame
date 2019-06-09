#ifndef RECIBIR_INPUT_H
#define RECIBIR_INPUT_H

#include "cola_protegida.h"
#include "protocolo.h"
#include "threads.h"

class RecibirInput : public Thread {
private:
    ColaProtegida& cola;
    Protocolo& protocolo;
    bool terminar;

public:
    explicit RecibirInput(ColaProtegida& cola, Protocolo& protocolo);

    void run() override;

    void terminar();

    ~RecibirInput();
};

#endif

