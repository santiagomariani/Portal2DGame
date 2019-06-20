#include "partida.h"
#include "proceso_cliente.h"
#include "socket_error.h"
#include "cuerpo_a_enviar.h"
#include "ids.h"
#include "contador_tiempo.h"
#include <iostream>

#define FPS 60
#define TICKS_POR_FOTOGRAMA 1245/FPS

Partida::Partida(Fisica& fisica, SktAceptador skt,
                 int cant_clientes):
                fisica(fisica),
                skt_aceptador(std::move(skt)),
                continuar_juego(true){
    this->cant_clientes = cant_clientes;
    this->recibir_clientes = true;
}

InfoCuerpoBox2D Partida::obtenerInfo(Cuerpo* cuerpo){
    InfoCuerpoBox2D info;
    info.id = (uint8_t)cuerpo->getId();
    info.angulo = (int32_t)cuerpo->getAngle();
    info.pos = cuerpo->getPosition();
    info.ancho = (float32)cuerpo->getMaxWidth();
    info.alto = (float32)cuerpo->getMaxHeight();
    if (info.id == ID_CHELL){
        info.estado = (uint8_t)((Chell*)cuerpo)->obtenerEstado();
        info.orientacion = (uint8_t)((Chell*)cuerpo)->obtenerOrientacion();
        info.id_chell = (uint8_t)((Chell*)cuerpo)->getIdPersonaje();
    } else {
        info.estado = 0;
        info.orientacion = 0;
        info.id_chell = 0;
    }
    return info;
}


void Partida::correrPartida(){
    ContadorTiempo capTimer;

    while (this->continuar_juego){

        if (this->fisica.cantChells() == 0){
            this->continuar_juego = false;
            break;
        }

        capTimer.comenzar();
        Input input;
        if (this->cola_input.pop(input)){
            if (input.chell_muerta == 1){
                std::cout << "chell muerta\n";
                this->fisica.eliminarChell(input.id);
            } else {
                this->fisica.agregarTeclado(input.id, input.estado_teclado);
                this->fisica.agregarMouse(input.id, input.estado_mouse);
            }
        }
        
        this->fisica.actualizar();

        std::vector<Cuerpo*> cuerpos = this->fisica.obtenerCuerpos();

        for (auto it=cuerpos.begin(); it!=cuerpos.end(); it++){
            CuerpoAEnviar cuerpo_a_enviar;
            cuerpo_a_enviar.info_cuerpo = obtenerInfo(*it);
            cuerpo_a_enviar.ultimo = false;
            for (auto c=colas_clientes.begin(); c!=colas_clientes.end(); c++){
                (*c)->push(cuerpo_a_enviar);
            }
        }
        CuerpoAEnviar cuerpo_a_enviar;
        cuerpo_a_enviar.ultimo = true;
        for (auto c=colas_clientes.begin(); c!=colas_clientes.end(); c++){
            (*c)->push(cuerpo_a_enviar);
        }

        int frameTicks = capTimer.obtenerTicks();
        if (frameTicks < TICKS_POR_FOTOGRAMA) {
            SDL_Delay(TICKS_POR_FOTOGRAMA - frameTicks);
        }
    }

    for (auto it=colas_clientes.begin(); it!=colas_clientes.end(); it++){
        (*it)->finalizado();
    }

    for (size_t i = 0; i < this->threads_clientes.size(); ++i){
        this->threads_clientes[i]->terminar();
        this->threads_clientes[i]->join();
        this->threads_clientes[i].reset();
    }
}



int Partida::recibirClientes(){ 
    int i = 0;
    while (this->recibir_clientes && i < cant_clientes){
        try{
            Skt acept_skt = std::move(this->skt_aceptador.aceptarCliente());
            ColaBloqueanteCuerpos* c = new ColaBloqueanteCuerpos();
            colas_clientes.push_back(c);

            this->threads_clientes.emplace_back(new ProcesoCliente(
                                                std::move(acept_skt),
                                                this->cola_input,
                                                colas_clientes[i], i));
            i++;
            this->fisica.agregarNuevaChell();
        } catch(const SocketError &e){
            if (this->recibir_clientes){ // si no fue forzado
                std::cerr << "Error aceptando clientes:\n";
                std::cerr << e.what();
            }
            break;
        }
    }
    this->recibir_clientes = false;
    for (auto th=threads_clientes.begin(); th!=threads_clientes.end(); th++){
        (*th)->start();
    }
    this->skt_aceptador.cerrarCanales();
    this->skt_aceptador.cerrarSocket();
    return 0;
}

void Partida::terminarRecibirClientes(){
    this->recibir_clientes = false;
    this->skt_aceptador.cerrarCanales();
    this->skt_aceptador.cerrarSocket();
}

void Partida::terminar(){
    this->continuar_juego = false;
}


void Partida::run(){
    this->recibirClientes();
    this->correrPartida();
}

bool Partida::estaAceptando() {
    return this->recibir_clientes;
}


std::string Partida::obtenerPuerto() {
    return this->skt_aceptador.obtenerPuerto();
}

bool Partida::termino() {
    return !(this->continuar_juego);
}

Partida::~Partida(){
    for (uint i = 0; i < this->colas_clientes.size();i++){
        delete (colas_clientes[i]);
    }
    colas_clientes.clear();
}







