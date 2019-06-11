#include "iniciar_partida.h"

IniciarPartida::IniciarPartida(Partida& partida): partida(partida){
}

void IniciarPartida::run(){
	this->partida.comenzar();
}

void IniciarPartida::terminar(){
	this->partida.terminarPartida();
}

IniciarPartida::~IniciarPartida(){}

void IniciarPartida::terminar_recibir_clientes() {
    this->partida.terminarRecibirClientes();
}
