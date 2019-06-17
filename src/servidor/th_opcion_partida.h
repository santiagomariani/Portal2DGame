
#ifndef TH_OPCION_PARTIDA_H
#define TH_OPCION_PARTIDA_H

#include <skt.h>
#include "thread.h"
#include "manejador_partidas.h"


class ThOpcionPartida : public Thread {
    Skt skt;
    ManejadorPartidas& partidas;
    bool terminado;
public:
    ThOpcionPartida(Skt socket, ManejadorPartidas& partidas);
    void run() override;
    void terminar() override;
    ~ThOpcionPartida();
    
};


#endif //TH_OPCION_PARTIDA_H
