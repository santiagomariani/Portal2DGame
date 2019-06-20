#include <dirent.h>
#include "config.h"
#include "contact_listener.h"
#include "angulo_dos_setenta.h"
#include "ids.h"
#include "bloque_metal_diagonal.h"
#include "bloque_metal.h"
#include <iostream>
#include <sstream>
#include "manejador_partidas.h"
#include "receptor_arriba.h"
#include "boton.h"
#include "estado_logico.h"
#include "and.h"
#include "compuerta.h"
#include "emisor_arriba.h"
#include "emisor_abajo.h"
#include "emisor_derecha.h"
#include "emisor_izquierda.h"
#include "acido.h"
#include "barra_de_energia.h"

#define CANTIDAD_DE_CLIENTES 1

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

std::string ManejadorPartidas::elegirMapa(Protocolo& protocolo){
    std::unique_lock<std::mutex> lock(m);
    DIR* directorio;
    struct dirent* archivo;
    std::vector<std::string> mapas;
    if ((directorio = opendir ("mapas/")) != NULL) {
        while ((archivo = readdir(directorio)) != NULL) {
            mapas.emplace_back(archivo->d_name);
        }
        closedir (directorio);
        protocolo.enviarCantidad(mapas.size());
        for (auto it=mapas.begin(); it!=mapas.end(); ++it){
            protocolo.enviarNombreMapa(*it);
        }
    } else {

    }
    std::string nombre_mapa = protocolo.recibirNombreMapa();
    return std::move(nombre_mapa);
}

void ManejadorPartidas::nuevaPartida(Protocolo& protocolo) {
    //std::string nombre_mapa = std::move(elegirMapa(protocolo));
    std::unique_lock<std::mutex> lock(m);
    std::string nombre_mapa("prueba.yaml");
    mapas.emplace_back();
    CargadorMapa& mapa = mapas.back();
    mapa.cargarMapa(nombre_mapa);
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
    std::unique_lock<std::mutex> lock(m);
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


