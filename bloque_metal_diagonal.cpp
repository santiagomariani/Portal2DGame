
#include "bloque_metal_diagonal.h"
#include "ids.h"
#include <iostream>
#include "cuerpo.h"
#include <cmath>



BloqueMetalDiagonal::BloqueMetalDiagonal(int identidad, Mundo& mundo, const b2Vec2& pos, float angulo): 
    id(identidad), angulo(angulo),
    Bloque(TAMANIO_BLOQUE * 2, TAMANIO_BLOQUE * 2) {

    b2BodyDef cuerpo_def;
    cuerpo_def.type = b2_staticBody;
    cuerpo_def.position.Set(pos.x, pos.y);
    cuerpo_def.angle = angulo;
    cuerpo = mundo.agregarBody(cuerpo_def);

    b2PolygonShape polygonShape;
    b2Rot rotador(angulo);
    b2Vec2 vertices[2];
    vertices[0].Set(0,  0);
    vertices[1].Set(TAMANIO_BLOQUE/2,  0);
    vertices[1] = b2Mul(rotador, vertices[1]);
    vertices[2].Set(0, TAMANIO_BLOQUE/2);
    vertices[2] = b2Mul(rotador, vertices[2]);
  
    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, 2);

    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;

    cuerpo->CreateFixture(&myFixtureDef);
    cuerpo->SetUserData(this);
}

BloqueMetalDiagonal::BloqueMetalDiagonal(BloqueMetalDiagonal&& otro) : 
            Bloque(TAMANIO_BLOQUE * 2, TAMANIO_BLOQUE * 2){
    if (this == &otro){
        return;
    }
    maxWidth = otro.maxWidth;
    maxHeight = otro.maxHeight;

    otro.maxWidth = 0;
    otro.maxHeight = 0;
    cuerpo = otro.cuerpo;
    cuerpo->SetUserData(this);
    otro.cuerpo = nullptr;
}

const b2Vec2& BloqueMetalDiagonal::getPosition(){
    return cuerpo->GetPosition();
}

BloqueMetalDiagonal::crearMapaIds(){
    std::map<float, int> mapa;
}

int BloqueMetalDiagonal::getId(){
    if (angulo == 0){
        return ID_BLOQUE_DIAGONAL_0;
    }
    if (angulo == ){
        return ID_BLOQUE_DIAGONAL_0;
    }
    return ID_BLOQUE_METAL_DIAGONAL;
}

void BloqueMetalDiagonal::recibirDisparo(Disparo* disparo) {
    b2Vec2 bloque = this->getPosition();
    b2Vec2 pos = disparo->getPosition();
    pos -= bloque;
    if (std::abs(pos.x) >= std::abs(pos.y)){
        pos.y = 0;
    } else {
        pos.x = 0;
    }
    pos *= TAMANIO_BLOQUE / pos.Length();
    pos += bloque;

    b2Vec2 normal = pos - bloque;
    normal.Normalize();

    disparo->crearPortal(pos, normal);
}

void BloqueMetalDiagonal::empezarContacto(Cuerpo* otro){
    if (otro->getId() == ID_DISPARO){
        this->recibirDisparo((Disparo*)otro);
    }
}
