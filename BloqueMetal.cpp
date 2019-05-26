
#include "BloqueMetal.h"
#include "ids.h"
#include "cuerpo.h"

BloqueMetal::BloqueMetal(Mundo &mundo, b2Vec2& pos):
    Bloque(TAMANIO_BLOQUE_X * 2, TAMANIO_BLOQUE_Y * 2) {

    b2BodyDef cuerpo_def;
    cuerpo_def.type = b2_staticBody;
    cuerpo_def.position.Set(pos.x, pos.y);
    cuerpo = mundo.agregarBody(cuerpo_def);

    b2PolygonShape polygonShape;
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;

    polygonShape.SetAsBox(TAMANIO_BLOQUE_X, TAMANIO_BLOQUE_Y);
    cuerpo->CreateFixture(&myFixtureDef);
    cuerpo->SetUserData(this);
}

const b2Vec2& BloqueMetal::getPosition(){
    return cuerpo->GetPosition();
}
int BloqueMetal::getId(){
    return 1;
}

void BloqueMetal::recibirDisparo(Disparo *disparo) {
    b2Vec2 pos = this->getPosition();
    disparo->crearPortal(pos, pos); // esto esta mal..
}

void BloqueMetal::empezarContacto(Cuerpo* otro){
    if (otro->getId() == ID_DISPARO){
        this->recibirDisparo((Disparo*)otro);
    }
}
