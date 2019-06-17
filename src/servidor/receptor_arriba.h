#ifndef RECEPTORARRIBA_H
#define RECEPTORARRIBA_H

#define TAMANIO_SENSOR_Y 0.01

#include "cuerpo.h"
#include "mundo.h"
#include "receptor.h"

class ReceptorArriba : public Receptor {
public:
    ReceptorArriba(Mundo &mundo, const b2Vec2 &pos);
    uint8_t getId() override;

    ~ReceptorArriba();
};

#endif //RECEPTORARRIBA_H
