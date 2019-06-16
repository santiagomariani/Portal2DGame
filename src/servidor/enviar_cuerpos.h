#ifndef ENVIAR_CUERPOS_H
#define ENVIAR_CUERPOS_H

#include "ColaBloqueante.h"
#include "cola_bloqueante_cuerpos.h"
#include "Protocolo.h"
#include "Thread.h"

// Thread para enviar los cuerpos a un cliente

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

