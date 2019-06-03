//
// Created by santi on 31/05/19.
//

#ifndef BOLAENERGIA_H
#define BOLAENERGIA_H


#include <Box2D/Dynamics/b2Body.h>
#include "cuerpo.h"
#include "mundo.h"

#define RADIO_BOLAENERGIA 0.50f
#define DENSIDAD_BOLAENERGIA 1
#define CTE_VELOCIDAD_BOLAENERGIA 1

class BolaEnergia : public Cuerpo {
private:
    b2Body *cuerpo;
    Mundo& mundo;
    const unsigned int TIEMPO_VIDA = 150; // aprox. 13 segs.
    unsigned int contador;
    bool finalizo;
public:
    BolaEnergia(Mundo &mundo, b2Vec2 &pos, b2Vec2 &dir_vel);
    BolaEnergia(BolaEnergia &&otro);
    BolaEnergia& operator=(BolaEnergia &&otro);
    void actualizar() override;
    bool bolaFinalizo();
    const b2Vec2& getPosition();
    double getAngle();
    int getId();
    b2Body* getBody();
    void empezarContacto(Cuerpo *otro);
    void desactivar() override;
    void terminarContacto(Cuerpo *otro);
};

#endif //BOLAENERGIA_H
