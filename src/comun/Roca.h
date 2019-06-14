//
// Created by santi on 29/05/19.
//

#ifndef ROCA_H
#define ROCA_H


#include <Box2D/Common/b2Math.h>
#include "mundo.h"

class Roca : public Cuerpo {
private:
    b2Body* cuerpo;
    Mundo &mundo;
    b2Vec2 pos_inicial;
public:
    Roca(Mundo& mundo, const b2Vec2& pos);
    Roca(Roca &&otro);
    uint8_t getId() override;
    const b2Vec2& getPosition() override;
    b2Body* getBody();
    void resetear();
    virtual void empezarContacto(Cuerpo* otro);
    virtual void terminarContacto(Cuerpo* otro);
};

#endif //ROCA_H
