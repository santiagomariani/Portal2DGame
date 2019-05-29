#ifndef MUNDO_H
#define MUNDO_H

#include <map>
#include <utility>
#include <vector>
#include "cuerpo.h"
#include "Teletransportador.h"
#include "Box2D/Box2D.h"

class Portal;
class Mundo{
	b2World mundo;
	std::vector<Portal*> portales_activar;
	std::vector<Cuerpo*> cuerpos_desactivar;
	std::vector<Teletransportador> transportadores;
	std::vector<Cuerpo*> cuerpos_actualizar;
	void destruirCuerpos();	
	void activarPortales();
	void activarTeletransportadores();
public:
	void destruirBody(b2Body* body);
	Mundo(const b2Vec2& gravedad);
    //Mundo(Mundo &&otro);
    //Mundo& operator=(Mundo &&otro);

    void setContactListener(b2ContactListener& listener);

	b2Body* agregarBody(b2BodyDef& cuerpo_def);
	void actualizar();
	b2Body* obtenerBodies();

	void agregarPortal(Portal* portal);
	void agregarCuerpoADestruir(Cuerpo* cuerpo);
	void agregarTransportador(b2Body* cuerpo,
									 b2Vec2& nueva_pos,
									 b2Vec2& velocidad, 
									 float32 angulo = 0.0f);
	void agregarCuerpoAActualizar(Cuerpo* cuerpo);
	void actualizarCuerpos();
};

#endif //MUNDO_H
