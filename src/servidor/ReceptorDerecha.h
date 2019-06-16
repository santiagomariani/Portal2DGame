#ifndef RECEPTORDERECHA_H
#define RECEPTORDERECHA_H


#define TAMANIO_SENSOR_X 0.01

#include "cuerpo.h"
#include "mundo.h"
#include "Receptor.h"

class ReceptorDerecha : public Receptor {
public:
    ReceptorDerecha(Mundo &mundo, const b2Vec2 &pos);
    uint8_t getId() override;
};


#endif //RECEPTORDERECHA_H
