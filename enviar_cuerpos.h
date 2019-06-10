#ifndef ENVIAR_CUERPOS_H
#define ENVIAR_CUERPOS_H

#include "ColaBloqueante.h"
#include "protocolo.h"
#include "threads.h"


class EnviarCuerpos : public Thread {
private:
    ColaBloqueante<Cuerpo*>& cola;
    Protocolo& protocolo;
    bool terminar;

public:
    explicit EnviarCuerpos(ColaBloqueante<Cuerpo*>& cola, Protocolo& protocolo);

    void run() override;

    void terminar();

    ~EnviarCuerpos();
};

#endif

