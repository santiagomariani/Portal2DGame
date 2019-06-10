#ifndef PARTIDA_H
#define PARTIDA_H

#include "ColaBloqueante.h"
#include "fisica.h"
#include "threads.h"
#include <vector>
#include "SktAceptador.h"

class Partida{
    ColaBloqueante cola_input;
    Fisica& fisica;
    std::vector<Thread*> threads_clientes;
    std::vector<ColaBloqueante&> colas_clientes;
    SktAceptador skt_aceptador;
    bool continuar_juego;
    bool recibir_clientes;
public:
    Partida(Fisica& fisica, SktAceptador skt);
    void correrPartida();
    void terminarPartida();
    void recibirClientes();
    void terminarRecibirClientes();
    void comenzar();
    ~Partida();    
};

#endif


