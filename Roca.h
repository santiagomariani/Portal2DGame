//
// Created by santi on 29/05/19.
//

#ifndef ROCA_H
#define ROCA_H


#include <Box2D/Common/b2Math.h>
#include "mundo.h"

#define TAMANIO_ROCA 0.3f

class Roca : public Cuerpo {
private:
    b2Body* cuerpo;
public:
    Roca(Mundo& mundo, const b2Vec2& pos);
    Roca(Roca &&otro);
    int getId() override;
    const b2Vec2& getPosition() override;
    b2Body* getBody();
    virtual void empezarContacto(Cuerpo* otro);
    virtual void terminarContacto(Cuerpo* otro);
};

#endif //ROCA_H
