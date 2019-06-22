#include "fisica.h"
#include "estado_teclado.h"
#include "estado_mouse.h"
#include "chell.h"
#include "personajes.h"
#include "Box2D/Box2D.h"

Fisica::Fisica(Mundo& mundo):
				mundo(mundo), personajes(mundo, pos_chells){
}

void Fisica::actualizar(){
    this->personajes.actualizarChells();
	mundo.actualizar();
}

std::vector<Cuerpo*> Fisica::obtenerCuerpos(){
	std::vector<Cuerpo*> vector_cuerpos;
	b2Body *cuerpos = mundo.obtenerBodies();
	while (cuerpos){
		Cuerpo *actual = (Cuerpo*)cuerpos->GetUserData();
		if (!actual){
			cuerpos = cuerpos->GetNext();
			continue;
		}
		vector_cuerpos.push_back(actual);
		cuerpos = cuerpos->GetNext();
	}
	return vector_cuerpos;
}


void Fisica::agregarTeclado(int id, EstadoTeclado& teclado){
    this->personajes.agregarTeclado(id, teclado);
}

void Fisica::agregarMouse(int id, EstadoMouse& mouse){
    this->personajes.agregarClick(id, mouse);
}

void Fisica::agregarNuevaChell() {
    if (pos_chells.empty()){
        b2Vec2 pos(0, 0);
        personajes.agregar_chell(pos);
        return;
    }
    b2Vec2& pos = pos_chells.back();
    personajes.agregar_chell(pos);
    pos_chells.pop_back();
}

void Fisica::eliminarChell(int id_chell) {
    this->personajes.eliminarChell(id_chell);
}

int Fisica::cantChells() {
    return this->personajes.cantChells();
}

void Fisica::agregarPosChell(b2Vec2& pos_chell) {
    this->pos_chells.push_back(pos_chell);
}

int Fisica::cantSpawnPoints(){
	return this->pos_chells.size();
}


