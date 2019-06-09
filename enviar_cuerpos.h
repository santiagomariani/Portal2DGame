#ifndef ENVIAR_CUERPOS_H
#define ENVIAR_CUERPOS_H

#include "cola_protegida.h"
#include "protocolo.h"
#include "threads.h"


class EnviarCuerpos : public Thread {
private:
    ColaProtegida& cola;
    Protocolo& protocolo;
    bool terminar;

public:
    explicit EnviarCuerpos(ColaProtegida& cola, Protocolo& protocolo);

    void run() override;

    void terminar();

    ~EnviarCuerpos();
};

#endif

