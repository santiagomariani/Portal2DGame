
#include <config.h>
#include <contact_listener.h>
#include <angulo_dos_setenta.h>
#include <ids.h>
#include <bloque_metal_diagonal.h>
#include <bloque_metal.h>
#include <iostream>
#include "manejador_partidas.h"
#include "iniciar_partida.h"
#include "ReceptorArriba.h"
#include "boton.h"
#include "estado_logico.h"
#include "and.h"
#include "compuerta.h"
#include "EmisorArriba.h"
#include "EmisorAbajo.h"
#include "EmisorDerecha.h"
#include "EmisorIzquierda.h"
#include "Acido.h"
#include "BarraDeEnergia.h"

#define CANTIDAD_DE_CLIENTES 2

ManejadorPartidas::ManejadorPartidas() {

}

void ManejadorPartidas::nuevaPartida(std::string puerto, Protocolo& protocolo) {
    mapas.emplace_back();
    CargadorMapa& mapa = mapas.back();
    mapa.cargarMapa();
    Fisica& fisica = mapa.obtenerFisica();

    SktAceptador skt(puerto);
    skt.escucharClientes();

    partidas.emplace_back(new Partida(fisica, std::move(skt), CANTIDAD_DE_CLIENTES));


    // iniciar partida cree la partida adentro. (puede recibir el skt y nombre del mapa)
    // y partida tenga un mapa como atributo
    // y al iniciar la partida cargue el mapa del archivo
    // y el mapa tiene al mundo como atributo

    this->threads_partidas.emplace_back(new IniciarPartida(*(partidas.back())));
    threads_partidas[0]->start();
    protocolo.enviarPartidaCreada();
}

void ManejadorPartidas::terminarPartidas() {
    for (uint i = 0; i < threads_partidas.size(); i++){
        threads_partidas[i]->terminar();
        threads_partidas[i]->join();
    }
}

void ManejadorPartidas::enviarPartidasEsperando(Protocolo &protocolo) {
    for (auto it=partidas.begin(); it!=partidas.end(); it++){
        if ((*it)->estaAceptando()){
            std::string puerto = (*it)->obtenerPuerto();
            protocolo.enviarPuerto(puerto);
        }
    }
}


