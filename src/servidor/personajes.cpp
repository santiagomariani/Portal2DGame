#include "personajes.h"
#include <iostream>
#include <estado_mouse.h>
#include "estado_chell.h"

Personajes::Personajes(Mundo& m, std::vector<b2Vec2>& pos_chells) :
                       pos_chells(pos_chells), mundo(m){
	this->siguiente_client = 0;
}

int Personajes::agregar_chell(b2Vec2& pos){
	int id = this->siguiente_client;
	Chell chell(id, this->mundo);
	chell.activar(pos);
	this->personajes.emplace(id, std::move(chell)); //mov
	this->siguiente_client += 1;
	return id;
}

Chell& Personajes::obtener_chell(int chell_id){
	return this->personajes.at(chell_id);
}

void Personajes::agregarTeclado(int id, EstadoTeclado teclado){
    this->teclados[id] = teclado;
}

void Personajes::actualizarChells(){
    for (auto tc=teclados.begin(); tc!=teclados.end(); tc++){
        this->moverChell(tc->first, tc->second);
    }
}

void Personajes::moverChell(int chell_id, EstadoTeclado& teclado){
    Chell& chell = personajes.at(chell_id);
    chell.agarrarRoca(teclado);
    chell.mover(teclado);
}

void Personajes::agregarClick(int chell_id, EstadoMouse& mouse){
    Chell& chell = personajes.at(chell_id);
    if (mouse.clickDerecho()){
        b2Vec2 click = mouse.posClickDerecho();
        chell.dispararNaranja(click);
    }
    if (mouse.clickIzquierdo()){
        b2Vec2 click = mouse.posClickIzquierdo();
        chell.dispararAzul(click);
    }
}

void Personajes::eliminarChell(int id) {
    Chell& chell = personajes.at(id);
    chell.morir();
    teclados.erase(id);
}

int Personajes::cantChells() {
    return personajes.size();
}

