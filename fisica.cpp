#include "fisica.h"
#include "estado_teclado.h"
#include "estado_mouse.h"
#include "chell.h"
#include "personajes.h"
#include "Box2D/Box2D.h"


Fisica::Fisica(Protocolo& protocolo, Mundo& mundo): 
				mundo(mundo), personajes(mundo), protocolo(protocolo){
		personajes.agregar_chell();
}


void Fisica::actualizar(){
	EstadoTeclado teclado;
	EstadoMouse mouse;
    protocolo.recibirInput(teclado);
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

void Fisica::enviarCuerpos(){
	b2Body *cuerpos = mundo.obtenerBodies();
	while (cuerpos){
		Cuerpo *actual = (Cuerpo*)cuerpos->GetUserData();
		if (!actual){
			cuerpos = cuerpos->GetNext();
			continue;
		}
		protocolo.enviarCuerpo(*actual);
		cuerpos = cuerpos->GetNext();
	}
	protocolo.terminar();
}

