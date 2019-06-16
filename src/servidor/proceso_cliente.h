#ifndef PROCESO_CLIENTE_H
#define PROCESO_CLIENTE_H

#include "ColaBloqueante.h"
#include "cola_bloqueante_cuerpos.h"
#include "Protocolo.h"
#include "Thread.h"
#include "Input.h"
#include "cola_protegida.h"

// Thread para establecer el thread que envia
// los cuerpos del mundo a el clientes
// y el thread que recibe el input del cliente.

class ProcesoCliente : public Thread {
private:
	Skt socket;
    ColaProtegidaInput& cola_input;
    ColaBloqueanteCuerpos* cola_cuerpos;
    bool terminar_proceso;
    std::vector<Thread*> threads;
    uint8_t id;

public:
    explicit ProcesoCliente(Skt socket, 
    						ColaProtegidaInput& cola_input,
                            ColaBloqueanteCuerpos* cola_cuerpos,
    						uint8_t id);

    void run() override;
    void terminar() override;
    ~ProcesoCliente();
};

#endif
