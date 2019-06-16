
#include <config.h>
#include <contact_listener.h>
#include <angulo_dos_setenta.h>
#include <ids.h>
#include <bloque_metal_diagonal.h>
#include <BloqueMetal.h>
#include <iostream>
#include <sstream>
#include "manejador_partidas.h"
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

ManejadorPartidas::ManejadorPartidas(std::string& puerto_server):
                                     puerto_server(puerto_server){

}

void ManejadorPartidas::borrarPartidasTerminadas(){
    auto p = threads_partidas.begin();
    while (p != threads_partidas.end()){
        if ((*p)->termino()) {
            (*p)->join();
            p = threads_partidas.erase(p);
        } else {
            ++p;
        }
    }
}

void ManejadorPartidas::nuevaPartida(Protocolo& protocolo) {
    mapas.emplace_back();
    CargadorMapa& mapa = mapas.back();
    mapa.cargarMapa();
    Fisica& fisica = mapa.obtenerFisica();

    std::string nuevo_puerto = obtenerPuertoSiguiente();

    SktAceptador skt(nuevo_puerto);
    skt.escucharClientes();

    threads_partidas.emplace_back(new Partida(fisica, std::move(skt), CANTIDAD_DE_CLIENTES));
    threads_partidas.back()->start();

    protocolo.enviarPuerto(nuevo_puerto);

    borrarPartidasTerminadas();
}

void ManejadorPartidas::terminarPartidas(){
    for (uint i = 0; i < threads_partidas.size(); i++){
        threads_partidas[i]->terminar();
        threads_partidas[i]->join();
    }
}

void ManejadorPartidas::enviarPartidasEsperando(Protocolo &protocolo) {
    int cant_activos = 0;
    for (auto it=threads_partidas.begin(); it!=threads_partidas.end(); it++){
        if ((*it)->estaAceptando()){
            cant_activos++;
        }
    }
    protocolo.enviarCantidad(cant_activos);
    std::cout << "cant de partidas a enviar: " << cant_activos << std::endl;
    for (auto it=threads_partidas.begin(); it!=threads_partidas.end(); it++){
        if ((*it)->estaAceptando()){
            std::string puerto = (*it)->obtenerPuerto();
            protocolo.enviarPuerto(puerto);
            std::cout << "puerto enviado\n";
        }
    }
}

std::string ManejadorPartidas::obtenerPuertoSiguiente(){
    if (threads_partidas.empty()){
        std::string nuevo_puerto("8081");
        if (nuevo_puerto == puerto_server){
            nuevo_puerto = sumarPuerto(nuevo_puerto);
        }
        return nuevo_puerto;
    }
    std::string ultimo_puerto = threads_partidas.back()->obtenerPuerto();

    std::string nuevo_puerto = sumarPuerto(ultimo_puerto);
    if (nuevo_puerto == puerto_server){
        nuevo_puerto = sumarPuerto(nuevo_puerto);
    }
    return nuevo_puerto;
}

std::string ManejadorPartidas::sumarPuerto(std::string& puerto){
    int puerto_num;
    std::istringstream num_stream(puerto);
    num_stream >> puerto_num;

    puerto_num += 1;

    return std::to_string(puerto_num);
}


