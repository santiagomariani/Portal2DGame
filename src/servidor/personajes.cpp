#include "personajes.h"
#include <iostream>

Personajes::Personajes(Mundo& m) : mundo(m){
	this->siguiente_client = 0;
}

int Personajes::agregar_chell(){
	int id = this->siguiente_client;
	float posx = 2 + 1*id;
	float posy = 2;
	b2Vec2 pos(posx, posy); // POS INICIAL
	Chell chell(0, this->mundo);
	chell.activar(pos);
	this->personajes.emplace(id, std::move(chell)); //mov
	this->siguiente_client += 1;

    std::cout << "id: " << id << std::endl;
    std::cout << "pos_x: " << posx << std::endl;
    std::cout << "pos_y: " << posy << std::endl;
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