#ifndef RECEPTORIZQUIERDA_H
#define RECEPTORIZQUIERDA_H


#define TAMANIO_SENSOR_X 0.01

#include "cuerpo.h"
#include "mundo.h"
#include "Receptor.h"

class ReceptorIzquierda : public Receptor {
public:
    ReceptorIzquierda(Mundo &mundo, const b2Vec2 &pos);
    uint8_t getId() override;
};


#endif //RECEPTORIZQUIERDA_H
