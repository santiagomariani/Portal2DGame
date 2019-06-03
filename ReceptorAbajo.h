//
// Created by santi on 02/06/19.
//

#ifndef RECEPTORABAJO_H
#define RECEPTORABAJO_H

#define TAMANIO_SENSOR_X TAMANIO_RECEPTOR
#define TAMANIO_SENSOR_Y 0.01

#include "cuerpo.h"
#include "mundo.h"
#include "Receptor.h"

class ReceptorAbajo : public Receptor {
public:
    ReceptorAbajo(Mundo &mundo, const b2Vec2 &pos);
    int getId() override;
};

#endif //RECEPTORABAJO_H
