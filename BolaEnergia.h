//
// Created by santi on 31/05/19.
//

#ifndef BOLAENERGIA_H
#define BOLAENERGIA_H


#include <Box2D/Dynamics/b2Body.h>
#include "cuerpo.h"
#include "mundo.h"

#define RADIO_BOLAENERGIA 0.40f
#define DENSIDAD_BOLAENERGIA 1
#define CTE_VELOCIDAD_BOLAENERGIA 0.3

class BolaEnergia : public Cuerpo {
private:
    // bool ya_choque;
    b2Body *cuerpo;
    Mundo& mundo;
    const unsigned int TIEMPO_VIDA = 500;
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
    void desactivar();
    void agregarCuerpoADestruir();
    void empezarContacto(Cuerpo *otro);
    void terminarContacto(Cuerpo *otro);
};

#endif //BOLAENERGIA_H
