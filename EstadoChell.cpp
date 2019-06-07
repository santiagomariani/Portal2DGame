//
// Created by santi on 06/06/19.
//

#include <iostream>
#include "EstadoChell.h"

EstadoChell::EstadoChell(EstadoChell &&otro) {
    estado_actual = otro.estado_actual;
    orientacion_actual = otro.orientacion_actual;
}

void EstadoChell::actualizarEstado(SensorChell &s, b2Vec2 &vel) {

    if (vel.x > 0) {
        orientacion_actual = CHELL_MIRA_DERECHA;
    } else if (vel.x < 0) {
        orientacion_actual = CHELL_MIRA_IZQ;
    }

    if (s.estaActivado() && (abs(vel.x) == 0)) {
        estado_actual = CHELL_QUIETA;
    } else if (s.estaActivado() && (abs(vel.x)) > 0) {
        estado_actual = CHELL_MOVIENDOSE;
    } else if (!s.estaActivado()) {
        estado_actual = CHELL_EN_EL_AIRE;
    }
    std::cout << "ESTADO: " << unsigned(estado_actual) << std::endl;
    std::cout << "ORI: " << unsigned(orientacion_actual) << std::endl;
}

uint8_t EstadoChell::obtenerEstado() {
    return estado_actual;
}

uint8_t EstadoChell::obtenerOrientacion() {
    return orientacion_actual;
}
