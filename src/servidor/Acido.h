
#ifndef ACIDO_H
#define ACIDO_H

#include "cuerpo.h"
#include "mundo.h"

// Representa el acido que mata al personaje Chell
class Acido : Cuerpo {
private:
    b2Body *cuerpo;
public:
    Acido(Mundo &mundo, b2Vec2 &pos);
    const b2Vec2& getPosition();

    // Devuelve el ID del acido establecido en el arvhivo ids.h
    uint8_t getId();
    
    b2Body* getBody();
    void empezarContacto(Cuerpo* otro);
    void terminarContacto(Cuerpo* otro);
};

#endif //ACIDO_H
