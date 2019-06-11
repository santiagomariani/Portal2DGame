#ifndef PROCESO_CLIENTE_H
#define PROCESO_CLIENTE_H

#include "ColaBloqueante.h"
#include "cola_bloqueante_cuerpos.h"
#include "Protocolo.h"
#include "Thread.h"
#include "Input.h"


class ProcesoCliente : public Thread {
private:
	Skt socket;
    std::queue<Input>& cola_input;
    ColaBloqueanteCuerpos* cola_cuerpos;
    bool terminar_proceso;
    std::vector<Thread*> threads;
    int id;

public:
    explicit ProcesoCliente(Skt socket, 
    						std::queue<Input>& cola_input, 
    						ColaBloqueanteCuerpos* cola_cuerpos,
    						int id);

    void run() override;

    void terminar() override;

    ~ProcesoCliente();
};

#endif
