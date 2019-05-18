#include "personajes.h"

Personajes::Personajes(Mundo& m) : mundo(m){
	this->siguiente_client = 0;
}

int Personajes::agregar_chell(){
	int id = this->siguiente_client;
	b2Vec2 pos(0, 0); // POS INICIAL
	Chell chell(this->mundo.getMundo(), pos);
	this->personajes[id] = std::move(chell); //mov
	this->siguiente_client += 1;
	return id;
}

void Personajes::disparar(int chell_id, b2Vec2& click_pos){
	b2Vec2 pos_chell = this->personajes[chell_id].getPosition();
	this->mundo.crearDisparo(pos_chell, click_pos);
}

void Personajes::mover_chell(int chell_id, EstadoTeclado& teclado){
	this->personajes[chell_id].mover(teclado);
}


std::map<int, Chell>& Personajes::getPersonajes(){
	return this->personajes;
}
