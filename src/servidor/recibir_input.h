#ifndef RECIBIR_INPUT_H
#define RECIBIR_INPUT_H

#include "ColaBloqueante.h"
#include "Protocolo.h"
#include "Thread.h"
#include "Input.h"
#include "cola_protegida.h"

// Thread que recibe el input de un cliente constantemente,
// pusheandolo en una cola protegida.

class RecibirInput : public Thread {
private:
    ColaProtegidaInput& cola;
    Protocolo& protocolo;
    bool terminar_proceso;

    void iteracion();

public:
    explicit RecibirInput(ColaProtegidaInput& cola, Protocolo& protocolo);
    void run() override;
    void terminar() override;
    ~RecibirInput() = default;
};

#endif

