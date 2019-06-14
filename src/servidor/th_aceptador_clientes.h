

#ifndef TH_ACEPTADOR_CLIENTES_H
#define TH_ACEPTADOR_CLIENTES_H


#include <Thread.h>
#include "manejador_partidas.h"

class ThAceptadorClientes : public Thread{
    SktAceptador skt_aceptador;
    ManejadorPartidas partidas;
    std::vector<std::unique_ptr<Thread>> threads_clientes;
    bool terminado;
public:
    explicit ThAceptadorClientes(SktAceptador sktAceptador);
    void run() override;
    void terminar() override;
    ~ThAceptadorClientes() = default;


};


#endif
