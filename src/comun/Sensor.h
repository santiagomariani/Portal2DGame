//
// Created by santi on 02/06/19.
//

#ifndef SENSOR_H
#define SENSOR_H

#include "cuerpo.h"

class Sensor {
public:
    virtual void empezarContacto(Cuerpo* otro) = 0;
    virtual void terminarContacto(Cuerpo* otro) = 0;
};


#endif //SENSOR_H
