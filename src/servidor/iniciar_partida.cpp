#include "iniciar_partida.h"

// iniciar partida cree la partida adentro. (puede recibir el skt y nombre del mapa)
// y partida tenga un mapa como atributo
// y al iniciar la partida cargue el mapa del archivo
// y el mapa tiene al mundo como atributo

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
