//
// Created by santi on 04/06/19.
//

#ifndef BARRADEENERGIA_H
#define BARRADEENERGIA_H


#include "cuerpo.h"
#include "mundo.h"

#define TAMANIO_BARRAENERGIA_X 0.05
#define TAMANIO_BARRAENERGIA_Y 1

class BarraDeEnergia : public Cuerpo {
private:
    b2Body *cuerpo;
public:
    BarraDeEnergia(Mundo &mundo, b2Vec2 &pos);
    const b2Vec2& getPosition() override;
    uint8_t getId() override;
    b2Body* getBody() override;
    void empezarContacto(Cuerpo *cuerpo);
    void terminarContacto(Cuerpo *cuerpo);
};


#endif //BARRADEENERGIA_H
