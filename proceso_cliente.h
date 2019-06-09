#ifndef PROCESO_CLIENTE_H
#define PROCESO_CLIENTE_H

#include "cola_protegida.h"
#include "protocolo.h"
#include "threads.h"


class ProcesoCliente : public Thread {
private:
	Protocolo protocolo;
    ColaProtegida& cola_input;
    ColaProtegida& cola_cuerpos;
    bool terminar;
    std::vector<Thread*> threads;

public:
    explicit ProcesoCliente(Protocolo protocolo, 
    						ColaProtegida& cola_input, 
    						ColaProtegida& cola_cuerpos);

    void run() override;

    void terminar() override;

    ~ProcesoCliente();
};

#endif
