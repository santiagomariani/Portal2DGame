//
// Created by santi on 06/06/19.
//

#include <iostream>
#include "EstadoChell.h"

EstadoChell::EstadoChell() : estado_actual(CHELL_QUIETA),
    orientacion_actual(CHELL_MIRA_DERECHA) {
}

EstadoChell::EstadoChell(EstadoChell &&otro) {
    estado_actual = otro.estado_actual;
    orientacion_actual = otro.orientacion_actual;
}

void EstadoChell::actualizarEstado(SensorChell &s, b2Vec2 &vel) {

    uint8_t orientacion_nueva;
    uint8_t estado_nuevo;

    if (vel.x > 0) {
        orientacion_nueva = CHELL_MIRA_DERECHA;
    } else if (vel.x < 0) {
        orientacion_nueva = CHELL_MIRA_IZQ;
    } else {
        orientacion_nueva = orientacion_actual;
    }

    if (s.estaActivado() && orientacion_nueva != orientacion_actual) {
        estado_nuevo = CHELL_CAMBIA_ORIENTACION;
    } else if (s.estaActivado() && (abs(vel.x) == 0)) {
        estado_nuevo = CHELL_QUIETA;
    } else if (s.estaActivado() && (abs(vel.x)) > 0) {
        estado_nuevo = CHELL_MOVIENDOSE;
    } else if (!s.estaActivado()) {
        estado_nuevo = CHELL_EN_EL_AIRE;
    } else {
        estado_nuevo = estado_actual;
    }
    estado_actual = estado_nuevo;
    orientacion_actual = orientacion_nueva;

    std::cout << "ESTADO: " << unsigned(estado_actual) << std::endl;
    std::cout << "ORI: " << unsigned(orientacion_actual) << std::endl;
}

uint8_t EstadoChell::obtenerEstado() {
    return estado_actual;
}

uint8_t EstadoChell::obtenerOrientacion() {
    return orientacion_actual;
}
