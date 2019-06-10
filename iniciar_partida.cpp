#include "iniciar_partida.h"

IniciarPartida::IniciarPartida(Partida partida): partida(partida){
}

IniciarPartida::run(){
	this->partida.run();
}

IniciarPartida::terminar(){
	this->partida.terminarPartida();
}

IniciarPartida::~IniciarPartida(){}
