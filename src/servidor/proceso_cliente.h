#ifndef PROCESO_CLIENTE_H
#define PROCESO_CLIENTE_H

#include "cola_bloqueante.h"
#include "cola_bloqueante_cuerpos.h"
#include "protocolo.h"
#include "thread.h"
#include "input.h"
#include "cola_protegida.h"


class ProcesoCliente : public Thread {
private:
	Skt socket;
    ColaProtegidaInput& cola_input;
    ColaBloqueanteCuerpos* cola_cuerpos;
    bool terminar_proceso;
    std::vector<Thread*> threads;
    int id;

public:
    explicit ProcesoCliente(Skt socket, 
    						ColaProtegidaInput& cola_input,
                            ColaBloqueanteCuerpos* cola_cuerpos,
    						int id);

    void run() override;

    void terminar() override;

    ~ProcesoCliente();
};

#endif
