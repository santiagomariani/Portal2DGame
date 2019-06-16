#ifndef SENSORRECEPTOR_H
#define SENSORRECEPTOR_H


#include <Box2D/Dynamics/b2Body.h>
#include "cuerpo.h"
#include "Receptor.h"
#include "Sensor.h"

class Receptor;

// Sensor que sirve para detectar cuando una bola de energia
// ingresa en el receptor de bolas de energia y puede ser activado.

class SensorReceptor : public Sensor {
private:
    Receptor &receptor;
public:
    SensorReceptor(Receptor &receptor);
    void empezarContacto(Cuerpo *otro) override;
    void terminarContacto(Cuerpo *otro) override;
};


#endif //SENSORRECEPTOR_H
