//
// Created by santi on 02/06/19.
//

#ifndef RECEPTORIZQUIERDA_H
#define RECEPTORIZQUIERDA_H


#define TAMANIO_SENSOR_X 0.01
#define TAMANIO_SENSOR_Y TAMANIO_RECEPTOR

#include "cuerpo.h"
#include "mundo.h"
#include "Receptor.h"

class ReceptorIzquierda : public Receptor {
public:
    ReceptorIzquierda(Mundo &mundo, const b2Vec2 &pos);
    int getId() override;
};


#endif //RECEPTORIZQUIERDA_H
