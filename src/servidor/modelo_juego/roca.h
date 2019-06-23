
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
    // Crea la Roca en el mundo, con todas sus propiedades.
    Roca(Mundo& mundo, const b2Vec2& pos);
    Roca(Roca &&otro);
    // Devuelve el id asociado a la Roca.
    uint8_t getId() override;
    // Devuelve la posicion de la Roca.
    const b2Vec2& getPosition() override;
    // Devuelve el b2Body asociado a la Roca.
    b2Body* getBody();
    // La Roca vuelve a la posicion inicial.
    void resetear();
    virtual void empezarContacto(Cuerpo* otro);
    virtual void terminarContacto(Cuerpo* otro);
};

#endif //ROCA_H
