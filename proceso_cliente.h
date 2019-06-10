#ifndef PROCESO_CLIENTE_H
#define PROCESO_CLIENTE_H

#include "ColaBloqueante.h"
#include "protocolo.h"
#include "threads.h"
#include "Input.h"


class ProcesoCliente : public Thread {
private:
	Skt socket;
    ColaBloqueante<Input>& cola_input;
    ColaBloqueante<Cuerpo*>& cola_cuerpos;
    bool terminar;
    std::vector<Thread*> threads;

public:
    explicit ProcesoCliente(Skt socket, 
    						ColaBloqueante<Input>& cola_input, 
    						ColaBloqueante<Cuerpo*>& cola_cuerpos);

    void run() override;

    void terminar() override;

    ~ProcesoCliente();
};

#endif
