#ifndef PARTIDA_H
#define PARTIDA_H

#include "cola_protegida.h"
#include "fisica.h"
#include "threads.h"

class Partida{
    ColaProtegida& cola;
    Fisica& fisica;
    std::vector<Thread*> threads_clientes;
    bool continuar_juego;
    bool recibir_clientes;
public:
    Partida(ColaProtegida& cola, Fisica& fisica);
    void correrPartida();
    void terminarPartida();
    void recibirClientes();
    void terminarRecibirClientes();
    ~Partida();    
};

#endif


