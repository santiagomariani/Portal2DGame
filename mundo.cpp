#include "mundo.h"
#include "BloqueRoca.h"
#include "disparo.h"

Mundo::Mundo(const b2Vec2& gravedad) : mundo(gravedad){
	actualizando_cuerpos = false;
}

void Mundo::setContactListener(b2ContactListener& listener){
	mundo.SetContactListener(&listener);
}

b2Body* Mundo::agregarBody(b2BodyDef& cuerpo_def){
	return mundo.CreateBody(&cuerpo_def);
}

void Mundo::destruirBody(b2Body* body){
	if (actualizando_cuerpos) {
		cola_cuerpos_a_borrar.push((Cuerpo*)body->GetUserData());
	} else {
		for (auto it = cuerpos_actualizar.begin(); it != cuerpos_actualizar.end(); it++){
			if ((*it) == (Cuerpo*)body->GetUserData()) {
				cuerpos_actualizar.erase(it);
				break;
			}
		}
		mundo.DestroyBody(body);
	}
}

void Mundo::actualizar(){
	destruirCuerpos();
	activarPortales();
	activarTeletransportadores();
	actualizarCuerpos();
	mundo.Step(1.0f / 60.0f, 6, 2);
}

b2Body* Mundo::obtenerBodies(){
	return this->mundo.GetBodyList();
}

void Mundo::agregarPortal(Portal* portal){
	portales_activar.push_back(portal);
}
void Mundo::activarPortales(){
	for (auto it=portales_activar.begin(); it!=portales_activar.end(); it++){
		(*it)->activar();
	}
	portales_activar.clear();
}
void Mundo::agregarCuerpoADestruir(Cuerpo* cuerpo){
	cuerpos_desactivar.push_back(cuerpo);
}

void Mundo::destruirCuerpos(){
	for (auto it=cuerpos_desactivar.begin(); it!=cuerpos_desactivar.end(); it++){
		(*it)->desactivar();
	}
	cuerpos_desactivar.clear();
}

void Mundo::agregarTransportador(b2Body* cuerpo,
									 b2Vec2& nueva_pos,
									 b2Vec2& velocidad, 
									 float32 angulo){
	transportadores.emplace_back(cuerpo, nueva_pos, velocidad, angulo);
}

void Mundo::activarTeletransportadores(){
	for (auto it=transportadores.begin(); it!=transportadores.end(); it++){
		(*it).activar();
	}
	transportadores.clear();
}

void Mundo::agregarCuerpoAActualizar(Cuerpo* cuerpo){
	if (actualizando_cuerpos) {
		cola_cuerpos_a_agregar.push(cuerpo);
	} else {
		cuerpos_actualizar.push_back(cuerpo);
	}
}

void Mundo::actualizarCuerpos(){

    // Borro cuerpos en cola.
    while (!cola_cuerpos_a_borrar.empty()) {
        Cuerpo *cuerpo = cola_cuerpos_a_borrar.front();
        for (auto it = cuerpos_actualizar.begin(); it != cuerpos_actualizar.end(); it++){
            if ((*it) == cuerpo) {
                cuerpos_actualizar.erase(it);
                break;
            }
        }
        mundo.DestroyBody(cuerpo->getBody());
        cola_cuerpos_a_borrar.pop();
    }
    // Agrego cuerpos en cola.
    while (!cola_cuerpos_a_agregar.empty()) {
        cuerpos_actualizar.push_back(cola_cuerpos_a_agregar.front());
        cola_cuerpos_a_agregar.pop();
    }

	actualizando_cuerpos = true;

	for (auto it = cuerpos_actualizar.begin(); it != cuerpos_actualizar.end(); it++){
		(*it)->actualizar();
	}

	actualizando_cuerpos = false;
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