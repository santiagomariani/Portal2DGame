
#include "roca.h"
#include "ids.h"
#include "config.h"

Roca::Roca(Mundo &mundo, const b2Vec2 &pos) :
    Cuerpo(config::tam_roca * 2, config::tam_roca * 2) ,
    mundo(mundo) {
    b2BodyDef cuerpo_def;
    cuerpo_def.type = b2_dynamicBody;
    cuerpo_def.position.Set(pos.x, pos.y);
    cuerpo_def.fixedRotation = false;
    cuerpo = mundo.agregarBody(cuerpo_def);

    b2PolygonShape polygon_shape;
    b2FixtureDef fixture_def;
    fixture_def.shape = &polygon_shape;
    fixture_def.density = 100;
    fixture_def.friction = 100;
    polygon_shape.SetAsBox(config::tam_roca, config::tam_roca);
    cuerpo->CreateFixture(&fixture_def);
    pos_inicial = pos;
    cuerpo->SetUserData(this);
}

Roca::Roca(Roca &&otro) : mundo(otro.mundo){
    if (this == &otro){
        return;
    }
    maxWidth = otro.maxWidth;
    maxHeight = otro.maxHeight;
    cuerpo = otro.cuerpo;
    pos_inicial = otro.pos_inicial;

    otro.maxWidth = 0;
    otro.maxHeight = 0;
    otro.cuerpo = nullptr;
    otro.pos_inicial.Set(0, 0);

    cuerpo->SetUserData(this);
}

uint8_t Roca::getId() {
    return ID_ROCA;
}

const b2Vec2 &Roca::getPosition() {
    return cuerpo->GetPosition();
}

void Roca::empezarContacto(Cuerpo *otro) {
}

void Roca::terminarContacto(Cuerpo *otro) {
}

b2Body *Roca::getBody() {
    return cuerpo;
}

void Roca::resetear() {
    b2Vec2 vel(0, 0);
    mundo.agregarTransportador(cuerpo, pos_inicial, vel, 0);
}
