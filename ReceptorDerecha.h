//
// Created by santi on 02/06/19.
//

#ifndef RECEPTORDERECHA_H
#define RECEPTORDERECHA_H


#define TAMANIO_SENSOR_X 0.01
#define TAMANIO_SENSOR_Y TAMANIO_RECEPTOR

#include "cuerpo.h"
#include "mundo.h"
#include "Receptor.h"

class ReceptorDerecha : public Receptor {
public:
    ReceptorDerecha(Mundo &mundo, const b2Vec2 &pos);
    int getId() override;
};


#endif //RECEPTORDERECHA_H
