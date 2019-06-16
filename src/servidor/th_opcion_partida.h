
#ifndef TH_OPCION_PARTIDA_H
#define TH_OPCION_PARTIDA_H

#include <Skt.h>
#include "Thread.h"
#include "manejador_partidas.h"

// Thread que se comunica con un cliente para acordar si se va a crear una
// nueva partida o se va a unir a una ya existente.

class ThOpcionPartida : public Thread {
    Skt skt;
    ManejadorPartidas& partidas;
    bool terminado;
public:
    ThOpcionPartida(Skt socket, ManejadorPartidas& partidas);
    void run() override;
    void terminar() override;
    bool termino() override;
    ~ThOpcionPartida();  
};


#endif //TH_OPCION_PARTIDA_H
