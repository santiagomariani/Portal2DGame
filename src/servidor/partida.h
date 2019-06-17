#ifndef PARTIDA_H
#define PARTIDA_H

#include "cola_bloqueante.h"
#include "cola_bloqueante_cuerpos.h"
#include "fisica.h"
#include "thread.h"
#include <vector>
#include "skt_aceptador.h"
#include "cola_protegida.h"

class Partida{
private:
    //ColaBloqueante<Input> cola_input;
    ColaProtegidaInput cola_input;
    Fisica& fisica;
    std::vector<Thread*> threads_clientes;
    std::vector<ColaBloqueanteCuerpos*> colas_clientes;
    SktAceptador skt_aceptador;
    bool continuar_juego;
    bool recibir_clientes;
    int cant_clientes;
    InfoCuerpoBox2D obtenerInfo(Cuerpo *cuerpo);
public:
    Partida(Fisica& fisica, SktAceptador skt, int cant_clientes);
    void correrPartida();
    void terminarPartida();
    int recibirClientes();
    void terminarRecibirClientes();
    void comenzar();
    ~Partida();


};

#endif


