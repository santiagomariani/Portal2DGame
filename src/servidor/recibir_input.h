#ifndef RECIBIR_INPUT_H
#define RECIBIR_INPUT_H

#include "cola_bloqueante.h"
#include "protocolo.h"
#include "thread.h"
#include "input.h"
#include "cola_protegida.h"

class RecibirInput : public Thread {
private:
    ColaProtegidaInput& cola;
    Protocolo& protocolo;
    bool terminar_proceso;

public:
    explicit RecibirInput(ColaProtegidaInput& cola, Protocolo& protocolo);

    void run() override;

    void terminar() override;

    ~RecibirInput() = default;
};

#endif

