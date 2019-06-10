#include "fisica.h"
#include "estado_teclado.h"
#include "estado_mouse.h"
#include "chell.h"
#include "personajes.h"
#include "Box2D/Box2D.h"


Fisica::Fisica(Mundo& mundo): 
				mundo(mundo), personajes(mundo){
		personajes.agregar_chell();
}


void Fisica::actualizar(EstadoTeclado& teclado, EstadoMouse& mouse){
	int id = 0; // SUPER HARDCODE
	Chell& chell = personajes.obtener_chell(id);
	chell.agarrarRoca(teclado);
	chell.mover(teclado);
	if (mouse.clickDerecho()){
		b2Vec2 click = mouse.posClickDerecho();
		chell.dispararNaranja(click);
	}
	if (mouse.clickIzquierdo()){
		b2Vec2 click = mouse.posClickIzquierdo();
		chell.dispararAzul(click);
	}
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


