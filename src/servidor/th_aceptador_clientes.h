

#ifndef UNTITLED_TH_ACEPTADOR_CLIENTES_H
#define UNTITLED_TH_ACEPTADOR_CLIENTES_H


#include <thread.h>
#include "manejador_partidas.h"

class ThAceptadorClientes : public Thread{
    std::string puerto;
    ManejadorPartidas partidas;
    std::vector<Thread*> threads_clientes;

public:
    explicit ThAceptadorClientes(std::string puerto);
    void run() override;
    void terminar() override;
    ~ThAceptadorClientes() = default;
};


#endif //UNTITLED_TH_ACEPTADOR_CLIENTES_H
