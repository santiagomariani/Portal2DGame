
#ifndef UNTITLED_BLOQUE_H
#define UNTITLED_BLOQUE_H


#include "cuerpo.h"
#include "disparo.h"

#define TAMANIO_BLOQUE_X 0.5f
#define TAMANIO_BLOQUE_Y 0.5f


class Bloque : public Cuerpo{
protected:
    float maxWidth;
    float maxHeight;
    Bloque(float maxWidth, float maxHeight) :
            maxWidth(maxWidth),
            maxHeight(maxHeight),
            Cuerpo(maxWidth, maxHeight) {};
public:
    virtual void recibirDisparo(Disparo* disparo) = 0;
    virtual int getId() = 0;
    virtual const b2Vec2& getPosition() = 0;
    virtual void empezarContacto(Cuerpo* otro) = 0;
};


#endif //UNTITLED_BLOQUE_H
