#include "mundo.h"
#include "BloqueRoca.h"
#include "disparo.h"

Mundo::Mundo(const b2Vec2& gravedad) : mundo(gravedad){
}

void Mundo::setContactListener(b2ContactListener& listener){
	mundo.SetContactListener(&listener);
}

b2Body* Mundo::agregarBody(b2BodyDef& cuerpo_def){
	return mundo.CreateBody(&cuerpo_def);
}

void Mundo::destruirBody(b2Body* body){
	this->mundo.DestroyBody(body);
}

void Mundo::actualizar(){
	destruirCuerpos();
	mundo.Step(1.0f / 60.0f, 6, 2);
}

b2Body* Mundo::obtenerBodies(){
	return this->mundo.GetBodyList();
}
/*
void Mundo::agregarPortal(Portal* portal){
	portales_activar.push_back(portal);
}
void Mundo::activarPortales(){
	for (auto it=portales_activar.begin(); it!=portales_activar.end(); it++){
		(*it)->activar();
	}
	portales_activar.clear();
}*/
void Mundo::agregarCuerpoADestruir(Cuerpo* cuerpo){
	cuerpos_desactivar.push_back(cuerpo);
}

void Mundo::destruirCuerpos(){
	for (auto it=cuerpos_desactivar.begin(); it!=cuerpos_desactivar.end(); it++){
		(*it)->desactivar();
	}
	cuerpos_desactivar.clear();
}


/*
Mundo::Mundo(Mundo &&otro): mundo(otro.mundo) {
    if (this == &otro){
        return;
    }
    //mundo = std::move(otro.mundo);
    a_destruir = std::move(a_destruir);



    //portales_activar = std::move(portales_activar);
    //cuerpos_desactivar = std::move(cuerpos_desactivar);
}

Mundo& Mundo::operator=(Mundo &&otro) {
    if (this == &otro){
        return *this;
    }
    mundo = std::move(otro.mundo);
    	
	a_destruir = std::move(a_destruir);

    //portales_activar = std::move(portales_activar);
    //cuerpos_desactivar = std::move(cuerpos_desactivar);
    return *this;
}
*/