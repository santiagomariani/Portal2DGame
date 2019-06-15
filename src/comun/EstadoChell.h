//
// Created by santi on 06/06/19.
//

#ifndef ESTADOCHELL_H
#define ESTADOCHELL_H

#include "SensorChell.h"
#include "estado_teclado.h"

#define CHELL_EN_EL_AIRE 0
#define CHELL_MOVIENDOSE 1
#define CHELL_QUIETA 2
#define CHELL_CAMBIA_ORIENTACION 3
#define CHELL_MOVIENDOSE_Y_DISPARA 4
#define CHELL_QUIETA_Y_DISPARA 5
#define CHELL_EN_EL_AIRE_Y_DISPARA 6
#define CHELL_SALTA 7
#define CHELL_MUERE 8

#define CHELL_MIRA_DERECHA 0
#define CHELL_MIRA_IZQ 1

class EstadoChell {
private:
    uint8_t estado_actual;
    uint8_t orientacion_actual;
    bool disparo;
public:
    EstadoChell();
    EstadoChell(EstadoChell &&otro);
    void actualizarEstado(SensorChell &s, b2Vec2 &vel);
    void ocurrioDisparo();
    uint8_t obtenerEstado();
    uint8_t obtenerOrientacion();
    void chellMurio();
};


#endif //ESTADOCHELL_H
