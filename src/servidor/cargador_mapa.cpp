
#include <config.h>
#include <angulo_dos_setenta.h>
#include <iostream>
#include "ids.h"
#include "cargador_mapa.h"
#include "estado_logico.h"
#include "boton.h"
#include "and.h"

#include "yaml-cpp/yaml.h"

CargadorMapa::CargadorMapa():
		gravedad(0, config.gravedad),
		mundo(gravedad),
		fisica(mundo){
	mundo.setContactListener(listener);
}


void CargadorMapa::cargarMapa() {
	int id, identificador, x, y;
	YAML::Node archivo = YAML::LoadFile("prueba.yaml");
	for (auto it = archivo["Bloques"].begin(); it != archivo["Bloques"].end(); ++it){
		id = (*it)["Id"].as<int>();
		identificador = (*it)["Identificador"].as<int>();
		x = (*it)["X"].as<int>();
		y = (*it)["Y"].as<int>();

		switch(id){
			//El bloque roca y el bloque metal se crean distintos, no se cual esta bien
			case(ID_BLOQUE_ROCA):
				posiciones.emplace_back(x, y);
				bloques_roca.emplace_back(id, mundo, posiciones.back());
                break;
			case(ID_BLOQUE_METAL):
				posiciones.emplace_back(x, y);
				bloques_metal.emplace_back(mundo, posiciones.back());
                break;
		    case(ID_SPAWNPOINT):
		        posiciones.emplace_back(x, y);
		        fisica.agregarPosChell(posiciones.back());
		        break;
		}
	}
	for (auto it = archivo["Conexiones"].begin(); it != archivo["Conexiones"].end(); ++it){
	}
	/*
	posiciones.emplace_back(-12,0);
	angulos_dos_setenta.emplace_back();
	BloqueMetalDiagonal bloque_diago(mundo, posiciones.back(), angulos_dos_setenta.back());
	bloques_diagonal.push_back(std::move(bloque_diago));


	posiciones.emplace_back(-8, 0);
	rocas.emplace_back(mundo, posiciones.back());

	posiciones.emplace_back(-6, 0);
	rocas.emplace_back(mundo, posiciones.back());

	b2Vec2 pos(-40, -3);
	b2Vec2 inc(1, 0);
	for (int j = 0; j < 45; ++j){
		posiciones.emplace_back(pos.x, pos.y);
		bloques_metal.emplace_back(mundo, posiciones.back());
		pos += inc;
	}

	b2Vec2 pos_bloque(2, -3);
	b2Vec2 inc_pared(0, 1);
	for (int j = 0; j < 2; ++j){
		posiciones.emplace_back(pos_bloque.x, pos_bloque.y);
		bloques_metal.emplace_back(mundo, posiciones.back());
		pos_bloque += inc_pared;
	}
	pos_bloque.Set(2, 2);
	bloques_metal.emplace_back(mundo, posiciones.back());

// Receptores
	posiciones.emplace_back(-17, -2);

	//ReceptorArriba* receptor_arriba = new ReceptorArriba(mundo, posiciones.back());
	std::unique_ptr<ReceptorArriba> receptor_arriba(new ReceptorArriba(mundo, posiciones.back()));

	int i = 0;
	botones_y_receptores[i] = std::move(receptor_arriba);
	i++;

	posiciones.emplace_back(0, -2.35);
	//Boton* b = new Boton(posiciones.back(), mundo);
	std::unique_ptr<Boton> b(new Boton(posiciones.back(), mundo));
	botones_y_receptores[i] = std::move(b);
	i++;
//b2Vec2 pos_boton2(-4, -2.35);
//Boton b2(pos_boton2, mundo);

	//EstadoLogico* estado_boton = new EstadoLogico(*b); //usar unique pointer?
	std::shared_ptr<EstadoLogico> estado_boton(new EstadoLogico(*(botones_y_receptores[1])));
	compuertas_logicas[i] = std::move(estado_boton);
	i++;
//EstadoLogico* estado_boton2 = new EstadoLogico(b2);
	//EstadoLogico* estado_receptor = new EstadoLogico(*receptor_arriba);
	std::shared_ptr<EstadoLogico> estado_receptor(new EstadoLogico(*(botones_y_receptores[0])));
	compuertas_logicas[i] = std::move(estado_receptor);
	i++;

// con botones OR:
Or compuerta_or;
compuerta_or.agregar(estado_boton);
compuerta_or.agregar(estado_receptor);

b2Vec2 pos_compuerta(-1, -2);
Compuerta comp(pos_compuerta, mundo, compuerta_or);

// con botones AND:

	std::shared_ptr<And> compuerta_and(new And());
	//And* compuerta_and = new And();
	compuerta_and->agregar((compuertas_logicas[2]));
	compuerta_and->agregar((compuertas_logicas[3]));
	compuertas_logicas[i] = std::move(compuerta_and);

	posiciones.emplace_back(-1, -1.5);
	compuertas.emplace_back(posiciones.back(), mundo, *(compuertas_logicas[i]));

// Emisores 

	posiciones.emplace_back(-16, -2);
	emisores_arriba.emplace_back(mundo, posiciones.back());

	posiciones.emplace_back(-17, 2);
	emisores_abajo.emplace_back(mundo, posiciones.back());
	posiciones.emplace_back(-22, 1);
	emisores_derecha.emplace_back(mundo, posiciones.back());
	posiciones.emplace_back(-11, 1);
	emisores_izquierda.emplace_back(mundo, posiciones.back());

// Acido
	posiciones.emplace_back(-24, -2.5 + 0.06);
	acidos.emplace_back(mundo, posiciones.back());

// Barra Energia
	posiciones.emplace_back(-26, -1.5);
	barras_de_energia.emplace_back(mundo, posiciones.back());*/
}

Fisica &CargadorMapa::obtenerFisica() {
	return fisica;
}

CargadorMapa::~CargadorMapa() {
	for (auto it=botones_y_receptores.begin(); it!=botones_y_receptores.end(); it++){
		//delete it->second;
	}
	for (auto it=compuertas_logicas.begin(); it!=compuertas_logicas.end(); it++){
		//delete it->second;
	}
}


