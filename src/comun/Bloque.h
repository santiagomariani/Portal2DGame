
#ifndef UNTITLED_BLOQUE_H
#define UNTITLED_BLOQUE_H


#include "cuerpo.h"
#include "disparo.h"

class Bloque : public Cuerpo{
protected:
    float maxWidth;
    float maxHeight;
    Bloque(float maxWidth, float maxHeight) :
            Cuerpo(maxWidth, maxHeight),
            maxWidth(maxWidth),
            maxHeight(maxHeight){};
public:
    virtual void recibirDisparo(Disparo* disparo) = 0;
    virtual uint8_t getId() = 0;
    virtual const b2Vec2& getPosition() = 0;
    virtual void empezarContacto(Cuerpo* otro) = 0;
};


#endif //UNTITLED_BLOQUE_H
