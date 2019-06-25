
#ifndef BLOQUE_H
#define BLOQUE_H


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
    // Cada Bloque decide que hacer cuando recibe un disparo.
    virtual void recibirDisparo(Disparo* disparo) = 0;
    virtual uint8_t getId() = 0;
    virtual const b2Vec2& getPosition() = 0;
    virtual void empezarContacto(Cuerpo* otro) = 0;
    // Devuelve la velocidad final del objeto que rebote con el bloque
    virtual b2Vec2 obtenerVelocidadRebote(b2Vec2& vel_inicial) = 0;
};


#endif //BLOQUE_H
