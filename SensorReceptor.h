//
// Created by santi on 02/06/19.
//

#ifndef SENSORRECEPTOR_H
#define SENSORRECEPTOR_H


#include <Box2D/Dynamics/b2Body.h>
#include "cuerpo.h"
#include "Receptor.h"
#include "Sensor.h"

class Receptor;
class SensorReceptor : public Sensor {
private:
    Receptor &receptor;
public:
    SensorReceptor(Receptor &receptor);
    void empezarContacto(Cuerpo *otro) override;
    void terminarContacto(Cuerpo *otro) override;
};


#endif //SENSORRECEPTOR_H
