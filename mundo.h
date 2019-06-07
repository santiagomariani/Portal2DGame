#ifndef MUNDO_H
#define MUNDO_H

#include <map>
#include <utility>
#include <vector>
#include "cuerpo.h"
#include "Teletransportador.h"
#include "Box2D/Box2D.h"
#include <queue>

class Portal;
class Mundo{
private:
	bool actualizando_cuerpos;
	std::queue<Cuerpo*> cola_cuerpos_a_agregar;
	std::queue<Cuerpo*> cola_cuerpos_a_borrar;
	std::vector<Portal*> portales_activar;
	std::vector<Cuerpo*> cuerpos_desactivar;
	std::vector<Teletransportador> transportadores;
	std::vector<Cuerpo*> cuerpos_actualizar;
	std::vector<b2Joint*> joints_a_destruir;
	b2World mundo;
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
	void agregarJointADestruir(b2Joint* joint);
	void destruirJoints();
	void agregarTransportador(b2Body* cuerpo,
									 b2Vec2& nueva_pos,
									 b2Vec2& velocidad, 
									 float32 angulo = 0.0f);
	void agregarCuerpoAActualizar(Cuerpo* cuerpo);
	void actualizarCuerpos();
};

#endif //MUNDO_H
