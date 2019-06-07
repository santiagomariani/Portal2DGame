//
// Created by santi on 06/06/19.
//

#ifndef SENSORCHELL_H
#define SENSORCHELL_H


#include "Sensor.h"

class SensorChell : public Sensor {
private:
    bool activado;
    int cant_contactos;
public:
    SensorChell();
    bool estaActivado();
    void empezarContacto(Cuerpo* otro) override;
    void terminarContacto(Cuerpo* otro) override;
};


#endif //SENSORCHELL_H
