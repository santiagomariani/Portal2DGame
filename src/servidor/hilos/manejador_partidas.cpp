#include <dirent.h>
#include "config.h"
#include "contact_listener.h"
#include "angulo_dos_setenta.h"
#include "ids.h"
#include "bloque_metal_diagonal.h"
#include "bloque_metal.h"
#include <iostream>
#include <sstream>
#include <path.h>
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

bool ManejadorPartidas::elegirMapa(Protocolo& protocolo, 
                                          std::string& nombre_mapa){
    DIR* directorio;
    struct dirent* archivo;
    std::vector<std::string> mapas;
    std::string dir = std::string(MAPAS) + "mapas/";
    if ((directorio = opendir(dir.c_str())) != NULL) {
        {
            std::unique_lock<std::mutex> lock(m);
            while ((archivo = readdir(directorio)) != NULL) {
                if (strcmp(archivo->d_name, ".") == 0 || 
                    strcmp(archivo->d_name,"..") == 0){
                    continue;
                }
                mapas.emplace_back(archivo->d_name);
            }
            closedir (directorio);
        }
        protocolo.enviarCantidad(mapas.size());
        for (auto it=mapas.begin(); it!=mapas.end(); ++it){
            protocolo.enviarNombreMapa(*it);
        }
    } else {
        // error leyendo dir...
    }
    uint8_t respuesta = protocolo.recibirCodigoMensaje();
    if (respuesta == MSJ_ACEPTAR){
        nombre_mapa.assign(protocolo.recibirNombreMapa());
        return true;
    }
    return false;
}

bool ManejadorPartidas::nuevaPartida(Protocolo& protocolo) {
    std::string nombre_mapa;
    if (!elegirMapa(protocolo, nombre_mapa)){
        return false;
    }
    std::unique_lock<std::mutex> lock(m);
    this->mapas.emplace_back();
    CargadorMapa& mapa = mapas.back();
    lock.unlock();

    mapa.cargarMapa(nombre_mapa);
    Fisica& fisica = mapa.obtenerFisica();
    int spawn_points = fisica.cantSpawnPoints();

    std::string nuevo_puerto = obtenerPuertoSiguiente();

    SktAceptador skt(nuevo_puerto);
    skt.escucharClientes();
    {
        std::unique_lock<std::mutex> lock(m);
        threads_partidas.emplace_back(new Partida(fisica, std::move(skt), spawn_points));
        threads_partidas.back()->start();
    }

    protocolo.enviarPuerto(nuevo_puerto);
    return true;
}

void ManejadorPartidas::terminarPartidas(){
    for (uint i = 0; i < threads_partidas.size(); i++){
        threads_partidas[i]->terminar();
        threads_partidas[i]->join();
    }
}

bool ManejadorPartidas::enviarPartidasEsperando(Protocolo &protocolo) {
    int cant_activos = 0;
    std::vector<std::string> puertos;
    std::string puerto;
    std::unique_lock<std::mutex> lock(m);
    for (auto it=threads_partidas.begin(); it!=threads_partidas.end(); it++){
        if ((*it)->estaAceptando()){
            puerto = (*it)->obtenerPuerto();
            puertos.emplace_back(puerto);
            cant_activos++;
        }
    }
    lock.unlock();
    protocolo.enviarCantidad(cant_activos);
    for (auto it=puertos.begin(); it!=puertos.end(); it++){
        protocolo.enviarPuerto(*it);
    }
    uint8_t msj = protocolo.recibirCodigoMensaje();
    if (msj != MSJ_ACEPTAR){
        return false;
    }
    return true;
}

std::string ManejadorPartidas::obtenerPuertoSiguiente(){
    std::unique_lock<std::mutex> lock(m);
    if (threads_partidas.empty()){
        std::string nuevo_puerto("8081");
        if (nuevo_puerto == puerto_server){
            nuevo_puerto = sumarPuerto(nuevo_puerto);
        }
        return nuevo_puerto;
    }
    std::string ultimo_puerto = threads_partidas.back()->obtenerPuerto();
    lock.unlock();
    
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


