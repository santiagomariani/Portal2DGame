#include "personajes.h"
#include <iostream>
#include <estado_mouse.h>

Personajes::Personajes(Mundo& m) : mundo(m){
	this->siguiente_client = 0;
}

int Personajes::agregar_chell(){
	int id = this->siguiente_client;
	float posx = 2 + 1*id;
	float posy = 2;
	b2Vec2 pos(posx, posy); // POS INICIAL
	Chell chell(id, this->mundo);
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

