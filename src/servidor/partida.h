#ifndef PARTIDA_H
#define PARTIDA_H

#include "ColaBloqueante.h"
#include "cola_bloqueante_cuerpos.h"
#include "fisica.h"
#include "Thread.h"
#include <vector>
#include "SktAceptador.h"
#include "cola_protegida.h"

// Thread que maneja el flujo de una partida mientras actualiza 
// la fisica del juego

class Partida : public Thread {
private:
    ColaProtegidaInput cola_input;
    Fisica& fisica;
    std::vector<std::unique_ptr<Thread>> threads_clientes;
    std::vector<ColaBloqueanteCuerpos*> colas_clientes;
    SktAceptador skt_aceptador;
    bool continuar_juego;
    bool recibir_clientes;
    int cant_clientes;
    InfoCuerpoBox2D obtenerInfo(Cuerpo *cuerpo);
public:
    // Recibe la cantidad de clientes que deben entrar para comenzar
    // la partida.
    Partida(Fisica& fisica, SktAceptador skt, int cant_clientes);
    void run() override;
    void terminar() override;
    bool termino() override;
    // Comienza el loop del juego.
    void correrPartida();
    // Comienza a recibir los clientes que van a jugar.
    int recibirClientes();
    void terminarRecibirClientes();
    // Devuelve si esta todavia aceptado clientes para 
    // entrar a la partida.
    bool estaAceptando();
    // Devuelve el puerto por el cual esta aceptando
    // clientes.
    std::string obtenerPuerto();
    ~Partida();
};

#endif


