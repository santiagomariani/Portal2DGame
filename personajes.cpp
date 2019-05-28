#include "personajes.h"

Personajes::Personajes(Mundo& m) : mundo(m){
	this->siguiente_client = 0;
}

int Personajes::agregar_chell(){
	int id = this->siguiente_client;
	b2Vec2 pos(2, 6); // POS INICIAL
	Chell chell(0, this->mundo);
	chell.activar(pos);
	this->personajes.emplace(id, std::move(chell)); //mov
	this->siguiente_client += 1;
	return id;
}

Chell& Personajes::obtener_chell(int chell_id){
	return this->personajes.at(chell_id);
}

/*
void Personajes::disparar(int chell_id, b2Vec2& click_pos){
	b2Vec2 pos_chell = this->personajes[chell_id].getPosition();
	pos_chell.x += 10;
	this->mundo.crearDisparo(pos_chell, click_pos);
}

void Personajes::mover_chell(int chell_id, EstadoTeclado& teclado){
	this->personajes[chell_id].mover(teclado);
}


std::map<int, Chell>& Personajes::getPersonajes(){
	return this->personajes;
}
*/