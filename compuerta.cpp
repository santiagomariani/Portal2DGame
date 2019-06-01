#include "compuerta.h"
#include "ids.h"
#include "estado_cerrada.h"
#include <iostream>

#define TAM_COMP_CUERPO_X 0.25
#define TAM_COMP_CUERPO_Y 0.5
#define TAM_COMP_BASE_X 0.15
#define TAM_COMP_BASE_Y 0.03

Compuerta::Compuerta(b2Vec2& pos, Mundo& mundo, CompuertaLogica& compuerta_logica):
                    Cuerpo(TAM_COMP_CUERPO_X*2,
                    TAM_COMP_CUERPO_Y*2 + TAM_COMP_BASE_Y*2),
                    compuerta_logica(compuerta_logica){

    // parte de ariba de la compuerta
    b2BodyDef cuerpo_def;
    cuerpo_def.type = b2_kinematicBody;
    cuerpo_def.position.Set(pos.x, pos.y);
    cuerpo = mundo.agregarBody(cuerpo_def);

    b2PolygonShape cuerpo_shape;
    b2FixtureDef cuerpo_fixture_def;
    cuerpo_fixture_def.shape = &cuerpo_shape;
    cuerpo_shape.SetAsBox(TAM_COMP_CUERPO_X, TAM_COMP_CUERPO_Y);
    cuerpo->CreateFixture(&cuerpo_fixture_def);
    cuerpo->SetUserData(this);

    // base de la compuerta
    b2BodyDef base_def;
    base_def.type = b2_kinematicBody;
    base_def.position.Set(pos.x, pos.y - TAM_COMP_CUERPO_Y - TAM_COMP_BASE_Y);
    base = mundo.agregarBody(base_def);

    b2PolygonShape base_shape;
    b2FixtureDef base_fixture_def;
    base_fixture_def.shape = &base_shape;

    base_shape.SetAsBox(0.1, TAM_COMP_BASE_Y);
    base->CreateFixture(&base_fixture_def);
    base->SetUserData(this);
    base->SetActive(false);

    mundo.agregarCuerpoAActualizar(this);

    estado = new EstadoCerrada();
}

bool Compuerta::estaActiva(){
    return compuerta_logica.encendida();
}

void Compuerta::actualizar(){
    if (estado){
        EstadoCompuerta* temp = estado->actualizar(estaActiva(), cuerpo);
        delete estado;
        estado = temp;
    }
}

void Compuerta::empezarContacto(Cuerpo* otro){
    estado->empezarContacto(otro);
}

int Compuerta::getId(){
    return estado->getId();
    //return ID_COMPUERTA;
}

const b2Vec2& Compuerta::getPosition(){
    return cuerpo->GetPosition();
}
