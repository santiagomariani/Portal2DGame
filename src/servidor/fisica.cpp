#include "fisica.h"
#include "estado_teclado.h"
#include "estado_mouse.h"
#include "chell.h"
#include "personajes.h"
#include "Box2D/Box2D.h"

Fisica::Fisica(Mundo& mundo): 
				mundo(mundo), personajes(mundo){
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
    personajes.agregar_chell();
}

void Fisica::eliminarChell(int id_chell) {
    this->personajes.eliminarChell(id_chell);

}

int Fisica::cantChells() {
    return this->personajes.cantChells();
}


