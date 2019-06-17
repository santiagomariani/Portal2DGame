#ifndef ENVIAR_CUERPOS_H
#define ENVIAR_CUERPOS_H

#include "cola_bloqueante.h"
#include "cola_bloqueante_cuerpos.h"
#include "protocolo.h"
#include "thread.h"


class EnviarCuerpos : public Thread {
private:
    ColaBloqueanteCuerpos* cola;
    Protocolo& protocolo;
    bool terminar_envio;

public:
    explicit EnviarCuerpos(ColaBloqueanteCuerpos* cola, Protocolo& protocolo);

    void run() override;

    void terminar();

    ~EnviarCuerpos();
};

#endif

