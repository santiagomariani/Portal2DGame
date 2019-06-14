//
// Created by santi on 02/06/19.
//

#ifndef RECEPTORARRIBA_H
#define RECEPTORARRIBA_H

#define TAMANIO_SENSOR_X TAMANIO_RECEPTOR
#define TAMANIO_SENSOR_Y 0.01

#include "cuerpo.h"
#include "mundo.h"
#include "Receptor.h"

class ReceptorArriba : public Receptor {
public:
    ReceptorArriba(Mundo &mundo, const b2Vec2 &pos);
    uint8_t getId() override;

    ~ReceptorArriba();
};

#endif //RECEPTORARRIBA_H
