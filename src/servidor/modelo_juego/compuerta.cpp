#include "compuerta.h"
#include "ids.h"
#include "estado_cerrada.h"
#include <iostream>
#include "config.h"

#define TAM_COMP_BASE_X 0.15
#define TAM_COMP_BASE_Y 0.06

Compuerta::Compuerta(b2Vec2& pos, Mundo& mundo):
                    Cuerpo(config.tam_compuerta_x*2,
                    config.tam_compuerta_y*2 + TAM_COMP_BASE_Y*2){

    // parte de ariba de la compuerta
    b2BodyDef cuerpo_def;
    cuerpo_def.type = b2_kinematicBody;
    cuerpo_def.position.Set(pos.x, pos.y);
    cuerpo = mundo.agregarBody(cuerpo_def);

    b2PolygonShape cuerpo_shape;
    b2FixtureDef cuerpo_fixture_def;
    cuerpo_fixture_def.shape = &cuerpo_shape;
    cuerpo_shape.SetAsBox(config.tam_compuerta_x, config.tam_compuerta_y);
    cuerpo->CreateFixture(&cuerpo_fixture_def);
    cuerpo->SetUserData(this);

    // base de la compuerta
    b2BodyDef base_def;
    base_def.type = b2_kinematicBody;
    base_def.position.Set(pos.x, pos.y - config.tam_compuerta_y - TAM_COMP_BASE_Y);
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
    if (!compuerta_logica){
        return false;
    }
    return compuerta_logica->encendida();
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

uint8_t Compuerta::getId(){
    return estado->getId();
    //return ID_COMPUERTA;
}

const b2Vec2& Compuerta::getPosition(){
    return cuerpo->GetPosition();
}

Compuerta::~Compuerta(){
    delete estado;
}

void Compuerta::agregarCompuertaLogica(std::shared_ptr<CompuertaLogica> compuerta) {
    compuerta_logica = compuerta;
}

Compuerta& Compuerta::operator=(Compuerta&& otra) {
    compuerta_logica = std::move(otra.compuerta_logica);
    cuerpo = otra.cuerpo;
    base = otra.base;
    estado = otra.estado;
}
