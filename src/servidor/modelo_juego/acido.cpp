#include "acido.h"
#include "ids.h"
#include "config.h"
#include "chell.h"

Acido::Acido(Mundo &mundo, b2Vec2 &pos) : Cuerpo(config.tam_acido_x * 2, config.tam_acido_y * 2){
    b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_def.position.Set(pos.x, pos.y);
    cuerpo = mundo.agregarBody(body_def);
    b2PolygonShape polygon_shape;
    b2FixtureDef fixture_def;
    fixture_def.isSensor = true;
    fixture_def.shape = &polygon_shape;
    polygon_shape.SetAsBox(config.tam_acido_x, config.tam_acido_y);
    cuerpo->CreateFixture(&fixture_def);
    cuerpo->SetUserData(this);
}

const b2Vec2 &Acido::getPosition() {
    return cuerpo->GetPosition();
}

uint8_t Acido::getId() {
    return ID_ACIDO;
}

b2Body *Acido::getBody() {
    return cuerpo;
}

void Acido::empezarContacto(Cuerpo *otro) {
    if (otro->getId() == ID_CHELL) {
        ((Chell*)otro)->morir();
    }
}

void Acido::terminarContacto(Cuerpo *otro) {

}
