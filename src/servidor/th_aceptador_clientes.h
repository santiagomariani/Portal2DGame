#ifndef TH_ACEPTADOR_CLIENTES_H
#define TH_ACEPTADOR_CLIENTES_H


#include <Thread.h>
#include "manejador_partidas.h"

// Thread para aceptar clientes constantemente.
// Una vez que llega un cliente, se crea otro thread para
// la comunicacion.

class ThAceptadorClientes : public Thread{
    SktAceptador skt_aceptador;
    ManejadorPartidas partidas;
    std::vector<std::unique_ptr<Thread>> threads_clientes;
    bool terminado;
public:
    ThAceptadorClientes(SktAceptador sktAceptador, std::string& puerto);
    void run() override;
    void terminar() override;
    ~ThAceptadorClientes() = default;


};


#endif
